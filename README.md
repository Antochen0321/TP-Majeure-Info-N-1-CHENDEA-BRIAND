**TP Majeure Info N1 CHENDEA BRIAND**

__Question 1:__
Dans cette question, nous devions créer une shell ensea, le but était simplement d'afficher le message d'acceuil et de rentrer dans notre invite de commande personnalisée.  
Voici ce que l'on voit lorsque l'on execute le code contenu dans le fichier "enseash.c" :  
On voit bien que lorsque l'on se place dans le bon répertoire et que l'on exécute ./enseash, on rentre dans notre micro-shell  
  
![Q1](screen/Q1.png)  
  
Le code associé à cette fonction se trouve dans le dossier Q1  
  
__Question 2:__  
Nous avions déjà crée une micro shell permettant d'executer des fonctions simples (si elles sont implémentées dans l'environnement de travail.  
Il fallait simplement importer 'fortune' et 'date' pour faire des tests simples:  
*sudo apt-get install fortune*  
*sudo apt-get install date*  

![Q2](screen/Q2.png) 
  
Le code associé à cette fonction se trouve aussi dans le dossier Q1 comme nous n'avons rien changé

__Question 3:__  
Nous avions déjà, lors de la question 1, implémenté le 'exit', on peut le voir sur la première capture d'écran, cependant, il fallait rajouter le code permettant d'implémenter le fait que ctrl + d permette de sortir aussi de notre micro-shell.  

Cette partie du code est écrite dans le dossier Q2.

__Question 4:__  
La partie de code ajoutée pour cette question est dans le dossier Q4. 
L'objectif est que notre invite de commande renvoie une expression différente en fonction des appels, en particulier qu'elle puisse signaler les erreurs de types 'Segmentation False' (pour laquelle elle renverra un 'sign'). Lorsque le preogramme appelé ne compile pas, il n'est pas reconnue par enseash qui renvoie un 'exit: 1'. Lorsqu'il compile et s'execute sans problème, elle renvoie un 'exit: 0', cependant, en cas de return dans la fonction, elle renvoie bien sûr la valeur appelée par le return.  
On regarde ce qui s'affiche pour une fonction (sans return) écrite de 3 manières:  
1) Non définie ou qui ne compile pas.  
2) Qui compile et s'execute sans problème
  
![fun1](Q4/fonctionV1.png)  
  
4) Qui comporte un segmentation false  
  
![fun1](Q4/fonctionV2.png)  
  
Et voici une capture de cmd lors de 3 appels successifs de myprogramm.c :

![Q4](Q4/Q4.png)  

__Question5:__  

