# Grafika-Projekt

Trello - https://trello.com/b/9rkByn3S/projekt-grafika

Dokument ze specyfikacją - https://linkd.pl/pppar

Projekt lotu statku na grafike

Specyfikacja 

Ogólny zarys projektu 

Tematem projektu jest interaktywna symulacja lotu statku kosmicznego. 

Celem gry jest bezpieczne dotarcie do planety (omijanie asteroid) i wylądowanie na niej bez rozbicia się (odpowiednia prędkość i kąt). 

 Sterowanie statkiem za pomocą myszki i klawiatury: 

-  	   w – przyśpieszenie do przodu 

-  	   s – przyśpieszenie do tyłu 

-      wertykalne ruchy myszką – sterowanie dziobem statku góra-dół (ang. pitch) 

-      horyzontalne ruchy myszką – obrót dzioba na prawo-lewo (ang. yaw) 

-      a, d – obrót wzdłuż osi statku (ang. roll) 

-      LPM – strzał, po 3 strzałach trafionych w asteroidę wybucha (asteroida) 

 

 

Opis:

- W kosmosie znajdować się będzie gwiazdy, wokół której będą orbitować planety, niektóre z nich posiadać będą księżyce. 

- Gwiazdy posiadać będą pole grawitacyjne ściągające statek. 

- W kosmosie znajdować się będą przemieszczające się asteroidy utrudniające lot. 

- Znajdować się także będą statyczne pole asteroid. 

- Statek będzie mógł wejść w kolizję z planetami, asteroidami: po trzech zderzeniach statek wybucha. 

- Statek będzie się odbijał od obiektów, z którymi się zderzył w zależności od prędkości. 

- Statek będzie mógł wejść w kolizję z gwiazdą: statek wybucha. 

- Tekstury zawierać będą statek, planety, asteroidy i gwiazda. 

- Zastosowanie techniki bump mapping do poprawienia jakości wyglądu tekstury planet i asteroid, by zasymulować nierówności ich powierzchni. 

- (Fizyka) Przyśpieszenie statku odwzorowane w sposób realistyczny. 

- Kamera będzie „przyczepiona” do statku z tyłu. 

- Źródłami światła będą reflektory statku kosmicznego i gwiazda. 

- Model oświetlenia – model Phonga. 

Particle effects: 

-      z dopalaczy statku będzie wydobywać się strumień gazów wylotowych 

-      statek będzie się dymił po kolizji z asteroidą, planetą 

-      statek wybucha po zniszczeniu 

 

- Technika Bloom zostanie użyta do poprawienia efektu światła gwiazdy. 

- Skybox - tekstura kosmosu. 

 

 

 

Fazy implementacji 

Na pierwszy deadline: 

- Pzyczepienie kamery do statku 

- Sterowanie statkiem (uproszczone) 

- Rozmieszczenie planet, asteroid, gwiazdy bez tekstur 

- Animacja planet, asteroid (orbitowanie, ruch po kosmosie) 

- Model oświetlenia 

- Tekstury 

- Bump mapping 

- Bloom (rendure to texture, potem sam efekt) 

- Skybox 

- Przygotowanie brył kolizji obiektów, które zostaną wykorzystane w symulacji fizycznej (chodzi o zdefiniowanie ksztaltow za pomoca bryl podstawowych – np. Sfera, prostopadloscian – w taki sposob, aby ustalic ich pozycje i rozmiary dla kazdego obiektu, mozna uzyc kilku bryl dla jednego obiektu). Wykrywanie kolizji z planetami, asteroidami (statek nie będzie przenikał) 




Na termin końcowy: 

- Fizyczny lot 

- Strzelanie 

- Particle effects 

- Odbijanie się statku od obiektów, z którymi się zderzył 
