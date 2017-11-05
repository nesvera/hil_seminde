phil.py [-h] [-a IP] [-p PORT] [-s SERIAL] [-b BAUD] [-t TOUT]

Descrição
---------
 Faz a comunicação através de UDP e serial entre o X-Plane e o microcontrolador.

Pacotes
-------
 Os pacotes são enviados em duas partes, com o pacote de início dado pelo
 caractere ```$```, finalizado por ```;*``` e delimitando os campos através de
 ```;```. Todos os campos são no padrão ponto flutuante IEEE-754 de precisão
 simples (32 bits).
 
 Exemplo:

```
  $0;c6f3927d;c3940595;c74ef5d6;00000000;b87c0bbe;00000000;387a9a7d;00000000;*
        X        Y         Z       Vx       Vy       Vz       q         p

  $1;00000000;3effcc3e;3c0a2d11;416cb74d;0000REFX;0000REFY;0000REFZ;0000REFH;*
        r       pitch    roll     yaw      ref x    ref y    ref z  ref pitch
```

Argumentos
----------

```
 -h, --help                 exibe esta mensagem e finaliza a execução
 -a IP, --address IP        IP do servidor (X-Plane) (padrão: 127.0.0.1)
 -p PORT, --port PORT       porta do servidor (X-Plane) (padrão: 5000)
 -s SERIAL, --serial SERIAL porta de comunicação serial (padrão: auto)
 -b BAUD, --baudrate BAUD   baudrate da comunicação serial (padrão: 9600)
 -t TOUT, --timeout TOUT    timeout da comunicação serial (padrão: 0)
```

Dependências
------------
 - Python 2.7
 - pySerial 3.0

TODO
----
 - Enviar comandos ao X-Plane;
 - Fazer interface para envio das referências;
 - Enviar referências por arquivo (?).
