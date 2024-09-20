"use strict";

// This is not a full .obj parser.
// see http://paulbourke.net/dataformats/obj/

function parseOBJ(text) {
  // because indices are base 1 let's just fill in the 0th data
  const objPositions = [[0, 0, 0]];
  const objTexcoords = [[0, 0]];
  const objNormals = [[0, 0, 0]];
  const objColors = [[0, 0, 0]];

  // same order as `f` indices
  const objVertexData = [
    objPositions,
    objTexcoords,
    objNormals,
    objColors,
  ];

  // same order as `f` indices
  let webglVertexData = [
    [],   // posicao
    [],   // coordenadas
    [],   // normais
    [],   // cores
  ];

  const materialLibs = [];
  const geometries = [];
  let geometry;
  let groups = ['default'];
  let material = 'default';
  let object = 'default';

  const noop = () => {};

  function newGeometry() {
    // If there is an existing geometry and it's
    // not empty then start a new one.
    if (geometry && geometry.data.position.length) {
      geometry = undefined;
    }
  }

  function setGeometry() {
    if (!geometry) {
      const position = [];
      const texcoord = [];
      const normal = [];
      const color = [];
      webglVertexData = [
        position,
        texcoord,
        normal,
        color,
      ];
      geometry = {
        object,
        groups,
        material,
        data: {
          position,
          texcoord,
          normal,
          color,
        },
      };
      geometries.push(geometry);
    }
  }

  function addVertex(vert) {
    const ptn = vert.split('/');
    ptn.forEach((objIndexStr, i) => {
      if (!objIndexStr) {
        return;
      }
      const objIndex = parseInt(objIndexStr);
      const index = objIndex + (objIndex >= 0 ? 0 : objVertexData[i].length);
      webglVertexData[i].push(...objVertexData[i][index]);
      // if this is the position index (index 0) and we parsed
      // vertex colors then copy the vertex colors to the webgl vertex color data
      if (i === 0 && objColors.length > 1) {
        geometry.data.color.push(...objColors[index]);
      }
    });
  }

  const keywords = {
    v(parts) {
      if (parts.length > 3) {
        objPositions.push(parts.slice(0, 3).map(parseFloat));
        objColors.push(parts.slice(3).map(parseFloat));
      } else {
        objPositions.push(parts.map(parseFloat));
      }
    },
    vn(parts) {
      objNormals.push(parts.map(parseFloat));
    },
    vt(parts) {
      objTexcoords.push(parts.map(parseFloat));
    },
    f(parts) {
      setGeometry();
      const numTriangles = parts.length - 2;
      for (let tri = 0; tri < numTriangles; ++tri) {
        addVertex(parts[0]);
        addVertex(parts[tri + 1]);
        addVertex(parts[tri + 2]);
      }
    },
    s: noop,    // smoothing group
    mtllib(parts, unparsedArgs) {
      materialLibs.push(unparsedArgs);
    },
    usemtl(parts, unparsedArgs) {
      material = unparsedArgs;
      newGeometry();
    },
    g(parts) {
      groups = parts;
      newGeometry();
    },
    o(parts, unparsedArgs) {
      object = unparsedArgs;
      newGeometry();
    },
  };

  const keywordRE = /(\w*)(?: )*(.*)/;
  const lines = text.split('\n');
  for (let lineNo = 0; lineNo < lines.length; ++lineNo) {
    const line = lines[lineNo].trim();
    if (line === '' || line.startsWith('#')) {
      continue;
    }
    const m = keywordRE.exec(line);
    if (!m) {
      continue;
    }
    const [, keyword, unparsedArgs] = m;
    const parts = line.split(/\s+/).slice(1);
    const handler = keywords[keyword];
    if (!handler) {
      console.warn('unhandled keyword:', keyword);  // eslint-disable-line no-console
      continue;
    }
    handler(parts, unparsedArgs);
  }

  // remove any arrays that have no entries.
  for (const geometry of geometries) {
    geometry.data = Object.fromEntries(
        Object.entries(geometry.data).filter(([, array]) => array.length > 0));
  }

  return {
    geometries,
    materialLibs,
  };
}

function parseMapArgs(unparsedArgs) {
  // TODO: handle options
  return unparsedArgs;
}

function parseMTL(text) {
  const materials = {};
  let material;

  const keywords = {
    newmtl(parts, unparsedArgs) {
      material = {};
      materials[unparsedArgs] = material;
    },
    /* eslint brace-style:0 */
    Ns(parts)       { material.shininess      = parseFloat(parts[0]); },
    Ka(parts)       { material.ambient        = parts.map(parseFloat); },
    Kd(parts)       { material.diffuse        = parts.map(parseFloat); },
    Ks(parts)       { material.specular       = parts.map(parseFloat); },
    Ke(parts)       { material.emissive       = parts.map(parseFloat); },
    map_Kd(parts, unparsedArgs)   { material.diffuseMap = parseMapArgs(unparsedArgs); },
    map_Ns(parts, unparsedArgs)   { material.specularMap = parseMapArgs(unparsedArgs); },
    map_Bump(parts, unparsedArgs) { material.normalMap = parseMapArgs(unparsedArgs); },
    Ni(parts)       { material.opticalDensity = parseFloat(parts[0]); },
    d(parts)        { material.opacity        = parseFloat(parts[0]); },
    illum(parts)    { material.illum          = parseInt(parts[0]); },
  };

  const keywordRE = /(\w*)(?: )*(.*)/;
  const lines = text.split('\n');
  for (let lineNo = 0; lineNo < lines.length; ++lineNo) {
    const line = lines[lineNo].trim();
    if (line === '' || line.startsWith('#')) {
      continue;
    }
    const m = keywordRE.exec(line);
    if (!m) {
      continue;
    }
    const [, keyword, unparsedArgs] = m;
    const parts = line.split(/\s+/).slice(1);
    const handler = keywords[keyword];
    if (!handler) {
      console.warn('unhandled keyword:', keyword);
      continue;
    }
    handler(parts, unparsedArgs);
  }

  return materials;
}


async function main() {
  /** @type {HTMLCanvasElement} */
  const canvas = document.querySelector("#canvas");
  const gl = canvas.getContext("webgl2");
  if (!gl) {
    return;
  }

  twgl.setAttributePrefix("a_");

  const vs = `#version 300 es
  in vec4 a_position;
  in vec3 a_normal;
  in vec2 a_texcoord;
  in vec4 a_color;

  uniform mat4 u_projection;
  uniform mat4 u_view;
  uniform mat4 u_world;
  uniform vec3 u_viewWorldPosition;

  out vec3 v_normal;
  out vec3 v_surfaceToView;
  out vec2 v_texcoord;
  out vec4 v_color;

  void main() {
    vec4 worldPosition = u_world * a_position;
    gl_Position = u_projection * u_view * worldPosition;
    v_surfaceToView = u_viewWorldPosition - worldPosition.xyz;
    v_normal = mat3(u_world) * a_normal;
    v_texcoord = a_texcoord;
    v_color = a_color;
  }
  `;

  const fs = `#version 300 es
  precision highp float;

  in vec3 v_normal;
  in vec3 v_surfaceToView;
  in vec2 v_texcoord;
  in vec4 v_color;

  uniform vec3 diffuse;
  uniform sampler2D diffuseMap;
  uniform vec3 ambient;
  uniform vec3 emissive;
  uniform vec3 specular;
  uniform float shininess;
  uniform float opacity;
  uniform vec3 u_lightDirection;
  uniform vec3 u_ambientLight;

  out vec4 outColor;

  void main () {
    vec3 normal = normalize(v_normal);
    vec3 surfaceToViewDirection = normalize(v_surfaceToView);
    vec3 halfVector = normalize(u_lightDirection + surfaceToViewDirection);

    float fakeLight = dot(u_lightDirection, normal) * .5 + .5;
    float specularLight = clamp(dot(normal, halfVector), 0.0, 1.0);

    vec4 diffuseMapColor = texture(diffuseMap, v_texcoord);
    vec3 effectiveDiffuse = diffuse * diffuseMapColor.rgb * v_color.rgb;
    float effectiveOpacity = opacity * diffuseMapColor.a * v_color.a;

    outColor = vec4(
        emissive +
        ambient * u_ambientLight +
        effectiveDiffuse * fakeLight +
        specular * pow(specularLight, shininess),
        effectiveOpacity);
  }
  `;

  const meshProgramInfo = twgl.createProgramInfo(gl, [vs, fs]);

  // Carregar o modelo do olho
  // O arquivo .mtl contém as informações das propriedades de refletividade do .obj. O comportamento real da luz (reflexão, sombras, etc.) 
  // é determinado pelo mecanismo de renderização (vertex shader, fragment shader)
  const objHref_olho = 'objetos/olho/olho.obj';  
  const response_olho = await fetch(objHref_olho);
  const text_olho = await response_olho.text();
  const obj_olho = parseOBJ(text_olho);

  // carregar materiais do .mtl
  const matTexts = await Promise.all(obj_olho.materialLibs.map(async filename => {
    const matHref = 'objetos/olho/olho.mtl';
    const response = await fetch(matHref);
    return await response.text();
  }));
  const materials = parseMTL(matTexts.join('\n'));

  // Criar textura padrão
  const textures = {
    defaultWhite: twgl.createTexture(gl, {src: [255, 255, 255, 255]}),
  };

  // Associar texturas a cada material
  for (const material of Object.values(materials)) {
    Object.entries(material)
      .filter(([key]) => key.endsWith('Map'))
      .forEach(([key, filename]) => {
        let texture = textures[filename];
        if (!texture) {
          const textureHref = 'objetos/olho/text/olho.png';
          texture = twgl.createTexture(gl, {src: (textureHref), flipY: true});
          textures[filename] = texture;
        }
        material[key] = texture;
      });
  }

  // Material padrão
  const defaultMaterial = {
    diffuse: [1, 1, 1],
    diffuseMap: textures.defaultWhite,
    ambient: [0, 0, 0],
    specular: [1, 1, 1],
    shininess: 400,
    opacity: 1,
  };

  // Criar partes do objeto do olho
  const parts_olho = obj_olho.geometries.map(({material, data}) => {
    if (data.color) {
      if (data.position.length === data.color.length) {
        data.color = { numComponents: 3, data: data.color };
      }
    } else {
      data.color = { value: [1, 1, 1, 1] };
    }
    const bufferInfo = twgl.createBufferInfoFromArrays(gl, data);
    const vao = twgl.createVAOFromBufferInfo(gl, meshProgramInfo, bufferInfo);
    return {
      material: {
        ...defaultMaterial,
        ...materials[material],
      },
      bufferInfo,
      vao,
    };
  });

  // Carregar o modelo da mesa
  const objHref_mesa = 'objetos/mesa/mesa.obj';  
  const response_mesa = await fetch(objHref_mesa);
  const text_mesa = await response_mesa.text();
  const obj_mesa = parseOBJ(text_mesa);

  // Carregar materiais do .mtl da mesa
  const matTexts2_mesa = await Promise.all(obj_mesa.materialLibs.map(async filename => {
    const matHref = 'objetos/mesa/mesa.mtl';
    const response = await fetch(matHref);
    return await response.text();
  }));
  const materials2 = parseMTL(matTexts2_mesa.join('\n')); // Parse dos materiais da mesa

  // Associar texturas para a mesa
  for (const material of Object.values(materials2)) {
    Object.entries(material)
      .filter(([key]) => key.endsWith('Map'))
      .forEach(([key, filename]) => {
        let texture = textures[filename];
        if (!texture) {
          // Carrega duas texturas diferentes para a mesa
          const textureHref = 'objetos/mesa/text/mesa.jpg';
          const textureHref2 = 'objetos/mesa/text/mesa2.jpg';
          texture = twgl.createTexture(gl, {src: (textureHref, textureHref2), flipY: true});
          textures[filename] = texture;
        }
        material[key] = texture; // Associar textura ao material da mesa
      });
  }

  // Criar partes do objeto da mesa
  const parts_mesa = obj_mesa.geometries.map(({material, data}) => {
    if (data.color) {
      if (data.position.length === data.color.length) {
        data.color = { numComponents: 3, data: data.color };
      }
    } else {
      data.color = { value: [1, 1, 1, 1] };
    }
    const bufferInfo = twgl.createBufferInfoFromArrays(gl, data);
    const vao = twgl.createVAOFromBufferInfo(gl, meshProgramInfo, bufferInfo);
    return {
      material: {
        ...defaultMaterial,
        ...materials2[material],
      },
      bufferInfo,
      vao,
    };
  });

  // Função para obter as extremidades de um conjunto de posições
  function getExtents(positions) {
    const min = positions.slice(0, 3);
    const max = positions.slice(0, 3);
    for (let i = 3; i < positions.length; i += 3) {
      for (let j = 0; j < 3; ++j) {
        const v = positions[i + j];
        min[j] = Math.min(v, min[j]);
        max[j] = Math.max(v, max[j]);
      }
    }
    return {min, max};
  }

  // Função para obter as extremidades de todas as geometrias
  function getGeometriesExtents(geometries) {
    return geometries.reduce(({min, max}, {data}) => {
      const minMax = getExtents(data.position);
      return {
        min: min.map((min, ndx) => Math.min(minMax.min[ndx], min)),
        max: max.map((max, ndx) => Math.max(minMax.max[ndx], max)),
      };
    }, {
      min: Array(3).fill(Number.POSITIVE_INFINITY),
      max: Array(3).fill(Number.NEGATIVE_INFINITY),
    });
  }


  const extents_olho = getGeometriesExtents(obj_olho.geometries);
  const range_olho = m4.subtractVectors(extents_olho.max, extents_olho.min);
  const extents_mesa = getGeometriesExtents(obj_mesa.geometries);
  const range_mesa = m4.subtractVectors(extents_mesa.max, extents_mesa.min);

  const objOffset_olho = m4.scaleVector(m4.addVectors(extents_olho.min, m4.scaleVector(range_olho, 0.5)), -1);
  // Alterar posição Y do olho
  objOffset_olho[1] += 3;
  
  const objOffset_mesa = m4.scaleVector(m4.addVectors(extents_mesa.min, m4.scaleVector(range_mesa, 0.5)), 1);
  // alterar posição Y da mesa
  objOffset_mesa[1] += -1;

  // Define o alvo da câmera para focar na cena
  const cameraTarget = [0, 1.5, 0];

  // Define o raio para a câmera a partir do tamanho do olho
  const radius = m4.length(range_olho) * 1.2;

  // inclinação da câmera no eixo Y.
  const cameraPosition = m4.addVectors(cameraTarget, [0, 0.3*radius, radius]);
  const zNear = radius / 100;
  const zFar = radius * 3;

  function degToRad(deg) {
    return deg * Math.PI / 180;
  }

  function render(time) {
    time *= 0.001;

    twgl.resizeCanvasToDisplaySize(gl.canvas);
    gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);
    gl.enable(gl.DEPTH_TEST);


    const fieldOfViewRadians = degToRad(120);

    // ajustar cena resolução da tela
    const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
    const projection = m4.perspective(fieldOfViewRadians, aspect, zNear, zFar);
    

    const up = [0, 1, 0];
    // Cria a matriz de transformaçào usando a posição da câmera, o alvo da câmera e o vetor "cima" 
    // cena é visualizada a partir da posição da câmera.
    const camera = m4.lookAt(cameraPosition, cameraTarget, up);
    const view = m4.inverse(camera);

    const sharedUniforms = {
      u_lightDirection: m4.normalize([-1, 3, 5]),
      u_view: view,
      u_projection: projection,
      u_viewWorldPosition: cameraPosition,
    };

    gl.useProgram(meshProgramInfo.program);
    twgl.setUniforms(meshProgramInfo, sharedUniforms);


    let u_world1 = m4.identity();
    u_world1 = m4.translate(u_world1, ...objOffset_olho); // Translação aplicada primeiro
    u_world1 = m4.yRotate(u_world1, time); // Rotação aplicada depois, garantindo que a rotação seja no próprio eixo

    for (const {bufferInfo, vao, material} of parts_olho) {
      gl.bindVertexArray(vao);
      twgl.setUniforms(meshProgramInfo, { u_world: u_world1 }, material);
      twgl.drawBufferInfo(gl, bufferInfo);
    }

    const mesaY = Math.sin(time * 2) * 0.3; // movimentar mesa para cima e para baixo

    // Mesa é um objeto muito maior que o olho. Dessa forma, foi preciso aplicar uma transformação
    // de escala. Assim, cada coordenada foi multiplicada pelo fator de escala aqui especificado.
    const scaleFactor = 0.014;
    const rotationAngle = Math.PI/2 // rotacionar mesa em 90 graus


    // objeto é transladado no eixo Y. Depois, é rotacionado em 90 graus
    let u_world2 = m4.translate(m4.identity(), objOffset_mesa[0], objOffset_mesa[1] + mesaY, objOffset_mesa[2]);
    u_world2 = m4.yRotate(u_world2, rotationAngle);
    u_world2 = m4.scale(u_world2, scaleFactor, scaleFactor, scaleFactor); // Aplica escala à mesa

    for (const {bufferInfo, vao, material} of parts_mesa) {
      gl.bindVertexArray(vao);
      twgl.setUniforms(meshProgramInfo, { u_world: u_world2 }, material);
      twgl.drawBufferInfo(gl, bufferInfo);
    }
    

    requestAnimationFrame(render);
  }

  requestAnimationFrame(render);
}

main();