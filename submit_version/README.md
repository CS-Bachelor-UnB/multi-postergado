# Multi-postergado
Trabalho de Sistemas Operacionais - UnB 2019

Autores:

* André Luís Souto Ferreira 14/0016261
* Otto Kristian von Sperling 12/0131510
* Victor Fabre Figueiredo 15/0022948

## Como executar?
### Compile os arquivos com:

    cd ~/root-dir-of-project/
    make

### Crie links simbólicos no diretório raiz dos executaveis em './bin/' com:

    make links

### Execute:
    
    ./escalonador -t topology &
    ./executa_postergado -f filename -d delay
    
> onde 'topology' pode ser fattree, hypercube, torus
> e 'delay' deve ser em segundos

## Come encerrar?
Para encerrar **todos** os escalonadores que você tenha ativado, **execute**:

    for pid in $(pidof escalonador); do kill -10 $pid; done

Para descobrir quais escalonadores **estão rodando no background**, **execute**:

    ps -p $(pidof escalonador)

> para encerrar apenas um dos escalonadores ativos, você pode usar o PID retornado no comando anterior:
    kill -10 <PID>

