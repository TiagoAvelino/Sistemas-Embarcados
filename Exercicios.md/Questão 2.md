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
6. Liste somente os arquivos com extensão .txt.

```C
arquivo.txt   cal_1996.txt  cal_2003.txt  cal_2010.txt  cal_2017.txt
cal_1990.txt  cal_1997.txt  cal_2004.txt  cal_2011.txt  cal_2018.txt
cal_1991.txt  cal_1998.txt  cal_2005.txt  cal_2012.txt  cal_2019.txt
cal_1992.txt  cal_1999.txt  cal_2006.txt  cal_2013.txt  cal_2020.txt
cal_1993.txt  cal_2000.txt  cal_2007.txt  cal_2014.txt  cal.txt
cal_1994.txt  cal_2001.txt  cal_2008.txt  cal_2015.txt  cal_types.txt
cal_1995.txt  cal_2002.txt  cal_2009.txt  cal_2016.txt
```

7. Liste somente os arquivos com extensão .png.
```C
BusinessTux.png               linux.png
linux1.png                    Tux-in-a-suit.png
linux2.png                    tux-linux-professional_0-100520358-orig.png
linux3.png                    TUX.png
linux_inside.png              xanderrun-tux-construction-8454.png
linux-penguin-icon-39742.png
```

8. Liste somente os arquivos com extensão .jpg.
```C
BusinessTux.png               linux.png
linux1.png                    Tux-in-a-suit.png
linux2.png                    tux-linux-professional_0-100520358-orig.png
linux3.png                    TUX.png
linux_inside.png              xanderrun-tux-construction-8454.png
linux-penguin-icon-39742.png
```
9. Liste somente os arquivos com extensão .gif.
```C
1086970.gif
```

10. Liste somente os arquivos que contenham o nome 'cal'.
```C
cal_1990.txt  cal_1997.txt  cal_2004.txt  cal_2011.txt  cal_2018.txt
cal_1991.txt  cal_1998.txt  cal_2005.txt  cal_2012.txt  cal_2019.txt
cal_1992.txt  cal_1999.txt  cal_2006.txt  cal_2013.txt  cal_2020.txt
cal_1993.txt  cal_2000.txt  cal_2007.txt  cal_2014.txt  cal.txt
cal_1994.txt  cal_2001.txt  cal_2008.txt  cal_2015.txt  cal_types.txt
cal_1995.txt  cal_2002.txt  cal_2009.txt  cal_2016.txt
cal_1996.txt  cal_2003.txt  cal_2010.txt  cal_2017.txt
```
11. Liste somente os arquivos que contenham o nome 'tux'.
```C
tux-linux-professional_0-100520358-orig.png
xanderrun-tux-construction-8454.png
```
12. Liste somente os arquivos que comecem com o nome 'tux'.
```C
tux-linux-professional_0-100520358-orig.png
```
