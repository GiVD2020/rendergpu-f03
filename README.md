# RenderGPU
Segona pràctica de GiVD 2020-21



**Abstract**

*(NOTA: Petit resum del què heu fet, no més de 200 paraules)*

**Features**



- Fase 1
    - Adaptació a la lectura de fitxers de dades
        - [x] Objectes  |  (Mario)
        - [x] Escenes virtuals  |  (Mario)
        - [x] Escenes de dades Reals | (Mario)
    -  [x] Material | Joan
    - Light
        - [x] Puntual | (Ignacio)
        - [ ] Direccional
        - [ ] Spotlight
        - [ ] Ambient Global
    - Shading
        - [x] Phong  |  (Estíbaliz)
        - [x] Gouraud  |  (Estíbaliz)
    - Textures
        - [x] Textura com material en un objecte | (Joan)
        - [x] Textura al pla base | (Mario)


- Fase 2 (OPT)
    - [x] Toon-shading i èmfasi de siluetes  |  (Estíbaliz)
    - [x] Mapping indirecte de textures | (Joan)
    - [ ] Animacions amb dades temporals
    - [ ] Normal mapping
    - [ ] Entorn amb textures
    - [ ] Reflexions
    - [ ] Transparencias via objectes.
    - [ ] Transparencias via environmental mapping.


**Extensions**

*(NOTA: Les extensions de la pràctica que heu fet i que no surten a la llista anterior)*


## Memòria
#### 1) Adaptació a la lectura de fitxers de dades
Primerament, hem adaptat totes les classes de la pràctica anterior de tal manera que encaixessin amb les noves classes (`/library`). D'aquesta manera hem fet també el aplicaTG a `Object.c`. A continuació hem creat la classe `FittedPlane` que hereda d'Object i implementa la creació d'un pla acotat.

Pel que fa a la càrrega de dades virtuals. Dins la classe `Builder` tenir el mètode que les carrega. Ara mateix esta configurat per a que agafi un fitxer de configuració hardcodejat. Per a que no sigui massa pesat executar les escenes. De totes maneres es podría fer també amb un dialog.

tipus d'objectes virtuals:
1. brobject
2. brobject traslladat

Podem trobar un exemple de 1. a `basic_spheres.txt` i de 2. a  basic_spheres_translate.txt`

**important!** quan es fa un `brobject` traslladat cal que el ".obj" estigui centrat a (0,0,0) per a que es faci correctament el trasllat.

Pel que fa a dades reals, el funcionament segueix el de la practica 1 en els fitxers de configuració. Es pot trobar algun exemple a `basic_data_test.txt`. A les screenshots es poden veure dos exemples amb dades reals.


### Comentari addicional:
S'han adaptat els fitxer d'entrada d'escenes virtual per a poder posar els materials:
+ `brobject ,route ,position ,difuse color`
+ `brobject ,route ,position ,difuse color ,especular color ,ambient color ,shineness`

Es pot trobar un exemple a `basic_spheres_translated_diffuse.txt`

##
#### 2) Material

En aquesta segona secció sen’s demana implementar la classe `Material` per a poder fer  el pas de les seves diverses components 
a la GPU. Per a fer això les modificacions que hem fet ha sigut afegir a la classe `Object` un atribut material, el qual es crearà junt amb els altres atributs d’objecte.

En el inici del  mètode draw de `Object` hem afegit la crida al mètode toGPU que passarà els seus valors a la GPU.
Aquesta comunicació la fem amb structs tant a la CPU com a la GPU.

Finalment, en el fitxer de vertexshader, agafem els valors de CPU. Per a fer això tenim un uniform de tipus struct amb les diverses components. 
Per comprobar que aquestes dades han sigut agafades correctament hem diverses execucions on cada cop el color serà igual a una component del material diferent.
La component shineness és la única que no és un vector, per tant per a setejar que el color sigui igual a ella hem creat un vec4 que cada component és igual al valor de shineness.

Els valors de cada component han sigut setejats en el constructor de la classe Material.
##
#### 5) Textures  

Per a poder passar les textures a la gpu hem agat d’afegir al buffer espai per a el vector de vertexstexture.
Com que inicialment només podem aplicar textures als objectes que el seu fitxer obj conté les coordenades de vt hem afegit un if comprobant que el vector on s’ha afegit aquestes coordenades no està buit, així els objectes que no tinguin textures no sel’s intentara aplicar la textura i evitarem errors.

OPCIONAL: Mapeig indirecte

En aquest apartat hem fet l’opcional de textures indirectes. Per a fer-ho, en els shaders de phong_texture_indirect hem modificat el codi per a que enlloc de passar desde el vshader a fshader les coordenades de textures que s’han enviat desde cpu, fem el càlcul de u,v.

A més tal i com hem explicat anteriorment els objectes que no tenen vt no sel’s pot aplicar textures, el que hem fet és que en la classe objecte, en el mètode make, al assignar els vertexs de la textura, en cas que no s’hagin llegit del fitxers els calcularem manualment amb la fòrmula de mapeig indirecte.
Així les spheres i alguns altres objectes també podran tenir textures.
En aquesta part hem tingut alguns problemes i actualment la textura no és mapejada correctament.

Per a poder provar els shaders de mapping inderecte hem afegit al menú de textures una nova opció, anomenada PhongTex Indirecte, habilitant aquesta opció podrem provar les textures indirectes.

##

## Screenshots
### 1) Adaptació a la lectura de fitxers de dades
`virtual_data.txt` i `configMapping.txt`

![Drag Racing](./resources/screenshots/virtualdata.png)

`basic_data_test.txt` i `configMappingData.txt`
![Drag Racing](./resources/screenshots/realdata1.png)

`basic_data_test.txt` amb les esferes juntes al pla y=0
![Drag Racing](./resources/screenshots/realdata2.png)

### 2) Material

Els valors de les diverses components han sigut setejades per a què s’ens mostrin les circumferències de color: vermell, verde, blau i blanc segons la component que usem.
En totes les execucions els valors són els mateixos però mostrem una component diferent. Per a deixar clar a quina correspon escribim junt a la imatge la component que és i quin valor té.

Component ambient = (1.0,0.0,0.0)

![Drag Racing](./resources/screenshots/ambient.png)


Component difusa = (0.0,1.0,0.0)

![Drag Racing](./resources/screenshots/difusa.png)


Component especular = (0.0,0.0,1.0)

![Drag Racing](./resources/screenshots/especular.png)


Shineness = 1.0

![Drag Racing](./resources/screenshots/shineness.png)


### 3) Light

AÑADIR AQUÍ LAS SCREENSHOTS DE LUZES


### 4) Shading
La següent imatge és la representació de les normales d'una esfera (`sphere0.obj`).

![Normales](./resources/screenshots/normals.PNG)

En totes les imatges d'ombre que es mostren la configuració que s'ha usat és la següent:
- Material: `ambient = (0.2,0.2,0.2)`, `diffuse = (0.8,0.5,0.5)`, `especular = (1.0,1.0,1.0)`, `shineness = 20`.
- Light: `iD_ = (0.8,0.8,0.8)`, `iS_ = (1,1,1)`, `iA_ = (0.2,0.2,0.2)`, `position_ = (10,10,20,0)`, `coeficients_ = (0,0,1)`
- Scene: `lightAmbientGlobal = (0.3, 0.3, 0.3)`

A continuació podem observar una esfera (`sphere0.obj`)a la que se li ha aplicat el sombrejat de Gouraud.

![Gouraud](./resources/screenshots/gouraud_ejemplo.PNG)

En aquesta imatge es pot apreciar l'ús del sombrejat de Phong en una esfera (`sphere0.obj`). Tot i que les diferències son poc perceptibles es pot observar que per a Phong la llum que visualitzem es troba més suavitzada, aquest resultat és l'esperat ja que al calcular les normals per a cada píxel, enlloc de per a cada vèrtex de la imatge, el resultat serà més 'natural' enlloc de tenir una apariencia més pixelada.

Per poder comparar les imatges obtingudes amb aquestes dues tècniques la millor opció es posar la component especular de la llum a (1,1,1).

![Phong](./resources/screenshots/phong_ejemplo.PNG)

Finalment, podem visualitzar com l'ombrejat de Toon en una  esfera (`sphere0.obj`) proporciona un efecte més pla del sombrejat de la esfera, fent-la semblar menys realista.

![Toon](./resources/screenshots/toon_ejemplo.PNG)

Destacar la consult de  [Simulació Gouraud/Phong](https://rabbid76.github.io/graphics-snippets/html/stackoverflow/gouraud_phong.html) per a visualitzar diverses figures amb les diferentes tècniques de shaders per a tal de poder comparar les imatges obtingudes.

### 5) Texture

La següent imatge ens mostra l'objecte `MonkeyTex.obj` amb la textura `MonkeyTex.png`, la configuració ha sigut la mateixa que s'ha utilitzat anteriorment.

![Drag Racing](./resources/screenshots/monkeyText.png)

La següent imatge ens mostra l'objecte `capsule.obj` amb la `textura 2k_earth_daymap.jpg`, la configuració ha sigut la mateixa que s'ha utilitzat anteriorment.

![Drag Racing](./resources/screenshots/capsuleText.png)

La següent imatge són les mateixes dades que l'anterior però aquest cop fent servir el mapeig indirecte de textures.

![Drag Racing](./resources/screenshots/capsuleTextIndirecte.png)

La següent imatge es correspon a l'objecte `sphere0.obj` sense llums i amb textura indirecte.

![Drag Racing](./resources/screenshots/sphereIndirecte.png)


Dades reals amb un pla amb textura. (Notem que hi ha força Z-fighting)

![Drag Racing](./resources/screenshots/fitted_plane_texture.png)

*(NOTA: Per a cada pas de l'enunciat (del 1 al 6), incloure captures de pantalla de les proves que heu fet per a demostrar la funcionalitat de la vostra pràctica amb explicacions de la seva configuració i com les heu aconseguides)*

*(NOTA2: Breu explicació, si cal, de com replicar els vostres resultats)*

**Additional Information**

*(NOTA: Hores de dedicació i problemes que heu tingut fent la pràctica)*
