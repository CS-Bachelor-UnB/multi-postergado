# multi-postergado
Trabalho de Sistemas Operacionais

Comunicação entre o escalonador e o job-scheduler será feita com caixa de mensagens não blocante.
3 modulos módulos pricipais: i) Escalonador ii) Executa_Postergado iii) Topologia do Escalonador

Etapas / Sprints:
1) ~~Executa_Postergado~~
2) Escalonador com tratamento de alarmes
  2.1) ~~Ler mensagens da fila de mensagens~~
  2.2) ~~Tratamento de Alarmes~~
  2.3) ~~Interface com a topologia escolhida (via linha de comando)~~
3) Topologias
4) Teste, Integração e Relatório

LEMBRE: entrega em CD

## Como executar?
Compile os arquivos com:

    cd ~/root-dir-of-project/
    make


Execute:
    
    cd ~/root-dir-of-project/bin
    escalonador -t topology &
    executa_postergado -f filename -d delay
    
> onde 'topology' pode ser fattree, hypercube, torus
> e 'delay' deve ser em segundos
