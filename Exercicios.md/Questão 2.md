Para todas as questões, escreva os comandos correspondentes no terminal.

1. Escreva o texto "Ola mundo cruel!" em um arquivo denominado "Ola_mundo.txt". Apresente o conteúdo deste arquivo no terminal.
  ```C
  $ echo Ola Mundo cruel !! > Ola_mundo.txt
  $ cat Ola_mundo.txt
  
  ```

2. Apresente o nome de todos os arquivos e pastas na pasta 'root'.
```C
  $ ls /

 ```
3. Apresente o tipo de todos os arquivos e pastas na pasta 'root'.
```C
  $ ls -l

 ```
4. Apresente somente as pastas dentro da pasta 'root'.
 ```C
  $ cd /
  $ ls -d */
   ```

5. Descubra em que dia da semana caiu o seu aniversário nos últimos dez anos.
  ```C
  alunos@LAB-SS-PC:~$ date -d "10 jun 2008"
  Ter Jun 10 00:00:00 -03 2008
  alunos@LAB-SS-PC:~$ date -d "10 jun 2009"
  Qua Jun 10 00:00:00 -03 2009
  alunos@LAB-SS-PC:~$ date -d "10 jun 2010"
  Qui Jun 10 00:00:00 -03 2010
  alunos@LAB-SS-PC:~$ date -d "10 jun 2011"
  Sex Jun 10 00:00:00 -03 2011
  alunos@LAB-SS-PC:~$ date -d "10 jun 2012"
  Dom Jun 10 00:00:00 -03 2012
  alunos@LAB-SS-PC:~$ date -d "10 jun 2013"
  Seg Jun 10 00:00:00 -03 2013
  alunos@LAB-SS-PC:~$ date -d "10 jun 2014"
  Ter Jun 10 00:00:00 -03 2014
  alunos@LAB-SS-PC:~$ date -d "10 jun 2015"
  Qua Jun 10 00:00:00 -03 2015
  alunos@LAB-SS-PC:~$ date -d "10 jun 2016"
  Sex Jun 10 00:00:00 -03 2016
  alunos@LAB-SS-PC:~$ date -d "10 jun 2017"
  Sáb Jun 10 00:00:00 -03 2017
  alunos@LAB-SS-PC:~$ date -d "10 jun 2018"
  Dom Jun 10 00:00:00 -03 2018
 ```
