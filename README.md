# Calcul d'intégral + plus représentation graphique

Un programme SDL(Nécessite l'installation de SDL pour être compilé et exécuté voir ci-dessous) en langage c 


<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu_poisson.png"><img src="images/image_menu_poisson.png" width="700" height="450"/></a>
  <br>
  Représentation graphique de la loi de poisson sur [0,10] et [0,13]!
 <table>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe_7.png"><img src="images/image_courbe_7.png" width="200" height="100"/></a>
  </td>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe_8.png"><img src="images/image_courbe_8.png" width="200" height="100"/></a>
  </td>
  </table><br>
  

</p>


## Prérequis
Téléchargement et installation du logiciel Code::Blocks disponible en téléchargement sur le lien suivant: http://www.commentcamarche.net/download/telecharger-34056352-code-blocks

1)Installation localement du compilateur MinGW disponible en téléchargement sur le lien suivant: https://sourceforge.net/projects/mingw-w64/

2) Cliquez sur install puis continue
3) Choisir mingw-developper-toolkit, mingw32-base, mingw32-gcc g++, msys-base comme sur
la capture ci-dessous:
<p align="center">
  <a href=""><img src="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/install-MinGW2.png" width="650" height="450"/></a>
</p>
4) Puis dans le menu « Installation » cliquez sur « Apply changes »
5) Les packages sont alors téléchargés
6) Quittez
7) Exécutez « C:\MinGW\msys\1.0\postinstall », aux questions posées, répondre
a. y (yes)
b. y (yes)
c. Donnez le chemin d’installation de mingw, c’est-à-dire à la racine du disque c: c:\mingw
<p align="center">
  <a href=""><img src="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/install-MinGW.png" width="700" height="450"/></a>
</p>
d. validez avec la touche entrée



Installation de la bibliothèque SDL qui permet de créer des graphiques dans la console disponible sur le lien suivant: https://www.libsdl.org/
Ensuite en bas à droite accéder à l'onglet download!
Une fois téléchargé rendez-vous dans le dossier d'installation du logiciel Code::Blocks et suivez-les étapes illustrer ci-dessous!


<p align="center">
  <a href=""><img src="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/install-sdl.png" width="700" height="450"/></a><br>
  Dézippé le contenu du dossier SDL à la racine du dossier du logiciel Code::Blocks<br>
  <a href=""><img src="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/install-sdl2.png" width="700" height="450"/></a><br>
  Assurez-vous bien que le dossier include contient bien le dossier SDL<br>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/install-sdl3.png"><img src="images/install-sdl3.png" width="700" height="450"/></a><br>
</p>
<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/newproject-sdl.png"><img src="images/newproject-sdl.png" width="700" height="450"/></a><br>
  Dans Code::Blocks faites file -> new project et choissisez un projet type SDL
  <br>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/newproject-sdl2.png"><img src="images/newproject-sdl2.png" width="700" height="450"/></a><br>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/newproject-sdl3.png"><img src="images/newproject-sdl3.png" width="700" height="450"/></a><br>
  Indiquez le chemin du dossier contenant le bibliothèque SDL normalement stocker <br>à la racine du dossier contenant le logiciel Code::Blocks!<br>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/newproject-sdl4.png"><img src="images/newproject-sdl4.png" width="700" height="450"/></a><br>
</p>

## Usage
Grâce à ce calculateur d'intégral vous allez pouvoir calculer l'intégral de n'importe quelle courbe en spécifiant la valeur des bornes inférieure et supérieure de l'intégral et également visualiser graphiquement l'air sous la courbe!
Voyez les illustrations ci-dessous!

<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu_stats.png"><img src="images/image_menu_stats.png" width="700" height="450"/></a>
  <br>
  Représentation graphique de la droite de régréssion linéaire d'une série statistique!
  <table>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe_stats.png"><img src="images/image_courbe_stats.png" width="200" height="100"/></a>
  </td>
  </table>
</p>

<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu_tengente.png"><img src="images/image_menu_tengente.png" width="700" height="450"/></a>
  <br>
  Représentation graphique d'une tengente avec sa droite d'équation de la forme y=f'(a)(x-a)+f(a)!
  <table>
   <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe8.png"><img src="images/image_courbe8.png" width="200" height="100"/></a>
  </td>
  </table>
</p>

<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu_binome.png"><img src="images/image_menu_binome.png" width="700" height="450"/></a>
  <br>
  Représentation graphique de la formule du binôme de Newton tel que ∀ n ∈ N Hn:(a+b)^n=∑k=0 jusqu'à n(k parmi n)a^(n−k)*b^k!<br>
  On remarque:<br>
  Pour des choix de valeurs a>b ==> Escalier à droite!<br>
  Pour des choix de valeurs b>a ==> Escalier à gauche!<br>
  Pour des choix de valeurs a=b ==> Escalier équilibré à droite et à gauche!<br>
  <table>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_binome1.png"><img src="images/image_binome1.png" width="200" height="100"/></a>
  </td>
      <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_binome2.png"><img src="images/image_binome2.png" width="200" height="100"/></a>
  </td>
    <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_binome3.png"><img src="images/image_binome3.png" width="200" height="100"/></a>
  </td>
  </table>
</p>

<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu_second_degree.png"><img src="images/image_menu_second_degree.png" width="700" height="450"/></a>
  <br>
  Représentation graphique d'un polynôme du second degré de la forme ax²+bx+c!
  
  <table>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe7.png"><img src="images/image_courbe7.png" width="200" height="100"/></a>
  </td>
      <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe8.png"><img src="images/image_courbe8.png" width="200" height="100"/></a>
  </td>
  <td valign='center'>
   <center> Intégral de -3x²+4x+3 sur [0,15]= -2882.699951<br>
   <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe9.png"><img src="images/image_courbe9.png" width="330" height="100"/></a>
   </center>
  </td>
  </table>
</p>


<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu_trajectoire.png"><img src="images/image_courbe_radioactivite.png" width="700" height="450"/></a>
  <br>
  Calcul de la trajectoire d'un projectile + représentation graphique!
  
  <table>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe_trajectoire.png"><img src="images/image_menu_radioactivite.png" width="200" height="100"/></a>
  </td>
  </table>
</p>

<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe_radioactivite.png"><img src="images/image_courbe_radioactivite.png" width="700" height="450"/></a>
  <br>
  Calcul de la décroissance radioactive + représentation graphique de la courbe!
  
  <table>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu_radioactivite.png"><img src="images/image_menu_radioactivite.png" width="200" height="100"/></a>
  </td>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu_radioactivite2.png"><img src="images/image_menu_radioactivite2.png" width="200" height="100"/></a>
  </td>
  </table>
</p>

<p align="center">
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_menu.png"><img src="images/image_menu.png" width="700" height="450"/></a>
  <center>Représentation graphique de la fonction x² sur [0,25] et [25,50] d'une fonction lineaire ax+b sur [0,25] et cos(x) sur [0,100]!</center>
  <table>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe.png"><img src="images/image_courbe.png" width="200" height="100"/></a>
  </td>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe2.png"><img src="images/image_courbe2.png" width="200" height="100"/></a>
  </td>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe3.png"><img src="images/image_courbe3.png" width="200" height="100"/></a>
  </td>
  <td>
  <a href="https://raw.githubusercontent.com/vertingo/Calcul_Graphique_Integral/master/images/image_courbe4.png"><img src="images/image_courbe4.png" width="200" height="100"/></a>
  </td></table><br>
</p>

<p align="center">
  <a href="https://www.youtube.com/channel/UC2g_-ipVjit6ZlACPWG4JvA?sub_confirmation=1"><img src="http://vertin-go.com/Fonctions_Annexes/annexes/pdt-page-de-telechargement/Android%20You%20Tube%20Data%20API/youtube2.png" width="400" height="250"/></a>
  <a href="https://www.facebook.com/vertingo/"><img src="http://vertin-go.com/Fonctions_Annexes/annexes/pdt-page-de-telechargement/Android%20You%20Tube%20Data%20API/rejoins_nous.png" width="400" height="250"/></a>
</p>
