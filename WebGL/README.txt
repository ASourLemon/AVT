Para correr com Google Chrome é necessário desativar opções de segurança devido a texturas...
Testado com IceWeasel e Internet Explorer

Bibliotica usada: glMatrix


========== Implementado ================
- Superfícies simples (quadrado, cubo, esfera)
- Desenho dos objetos da cena a partir dos objetos simples
- Movimento do sapo com o teclado
- Movimento dos objetos dinâmicos com incrementos de velocidade de 15 em 15 "ticks"
- Câmeras (ortogonal, perspetiva de topo, perspetiva 3ª pessoa) e respetiva mudança com o teclado
- Modo dia(luz direcional)/noite(spotlight) : tecla N
- Ciclo de jogo, colisões (colisões com objetos do rio está com bug. Com os carros está OK)
- Reflexões planares (blending + stencil)~


========== Em falta ================
- Cilindros
- Lens Flare
- HUD (extra, mas já realizado na versão OpenGL)
- Partículas
- Sombras (extra)
- Luzes pontuais (implementado incorretamente... necessário debug na passagem de parâmetro para o GLSL em LightManager.js)