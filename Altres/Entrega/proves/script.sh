clear
n=0
#n es el nombre de mains que tenim
m=0
#m es nombre de txt d'entrada que tenim

# Contem el nombre de casos de prova que hi ha
cont=0
while [ -f ./INPUT/$(( $cont + 1)).txt ] 
do
    cont=$(( $cont + 1))
done
m=$cont

# Contem el nombre de programes que hi ha
cont=1
while [ -d ./MAIN/$(( $cont + 1)) ] 
do
    cont=$(( $cont + 1))
done
n=$cont

echo "m: " $m " n: " $n

rm -R OUTPUT
mkdir OUTPUT

# Creem els directoris de sortida
i=1
while [ $i -le $n ]
do
    mkdir OUTPUT/$i
    chmod u+rwx ./MAIN/$i/pro2.exe
    i=$(( $i + 1 ))
done

# Executem els casos de prova
i=1
while [ $i -le $m ]
do
  echo "Joc de proves: " $i
  echo ""
  
  j=1
  while [ $j -le $n ]
    do
      echo "Usuari: " $j
      /usr/bin/time --format='Temps total: %E seg \nTemps user: %U seg \nTemps sistema: %S seg \nMemoria max: %M KB' ./MAIN/$j/pro2.exe < ./INPUT/$i.txt > ./OUTPUT/$j/$i.txt    
      j=$(( $j + 1 ))
      echo -e "\n"
    done
  i=$(( $i + 1 ))
  echo -e "--------------------------- \n"
done

# Executem el programa que genera la taula de patrons
touch in.txt
echo $n " " $m > in.txt
g++ -o main.exe main.cpp
./main.exe < in.txt
rm main.exe in.txt
exit
