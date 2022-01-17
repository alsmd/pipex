<h1> Pipex </h1>


<p>Projeto tem o foco em programar a funcionalidade pipe do shell na linguagem C</p>
<hr>

<p>Minha implementação utiliza um lista encadeada, onde cada item representa um comando a ser executado e os parametros que ele ira receber.</p>
<p>Comcei iterando sobre minha lista de traz para frente, fazendo com que cada comando criase um pipe com o comando anterior, assim como fazer com que cada comnaod fosse um processo separado.</p>
<p>Terminando minha iteração, todos os comandos estariam ligados para se comunicar.</p>
<p>Agora iterar novamente começando do primeiro comando, fazendo ele executar e passar o output para o input do proximo comando.</p>
