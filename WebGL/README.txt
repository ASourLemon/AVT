Para correr com Google Chrome � necess�rio desativar op��es de seguran�a devido a texturas...
Testado com IceWeasel e Internet Explorer

Bibliotica usada: glMatrix


========== Implementado ================
- Superf�cies simples (quadrado, cubo, esfera)
- Desenho dos objetos da cena a partir dos objetos simples
- Movimento do sapo com o teclado
- Movimento dos objetos din�micos com incrementos de velocidade de 15 em 15 "ticks"
- C�meras (ortogonal, perspetiva de topo, perspetiva 3� pessoa) e respetiva mudan�a com o teclado
- Modo dia(luz direcional)/noite(spotlight) : tecla N
- Ciclo de jogo, colis�es (colis�es com objetos do rio est� com bug. Com os carros est� OK)
- Reflex�es planares (blending + stencil)~


========== Em falta ================
- Cilindros
- Lens Flare
- HUD (extra, mas j� realizado na vers�o OpenGL)
- Part�culas
- Sombras (extra)
- Luzes pontuais (implementado incorretamente... necess�rio debug na passagem de par�metro para o GLSL em LightManager.js)