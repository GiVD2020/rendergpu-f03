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
        - [ ] Puntual
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
    - [ ] Mapping indirecte de textures
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

### Comentari addicional:
S'han adaptat els fitxer d'entrada d'escenes virtual per a poder posar els materials:
+ `brobject ,route ,position ,difuse color`
+ `brobject ,route ,position ,difuse color ,especular color ,ambient color ,shineness`

Es pot trobar un exemple a `basic_spheres_translated_diffuse.txt`

#### 4) Shading



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


### 3) Texture

Dades reals amb un pla amb textura. (Notem que hi ha força Z-fighting)

![Drag Racing](./resources/screenshots/fitted_plane_texture.png)

### 3) Shading

La siguiente imagen es la representación de las normales de una esfera (`sphere0.obj`).

![Normales](./resources/screenshots/normals.PNG)

En todas las imágenes del sombreado que se mostrarán seguidamente la configuración empleada ha sido la siguiente:
- Material: `ambient = (0.2,0.2,0.2)`, `diffuse = (0.8,0.5,0.5)`, `especular = (1.0,1.0,1.0)`, `shineness = 20`.
- Light: `iD_ = (0.8,0.8,0.8)`, `iS_ = (1,1,1)`, `iA_ = (0.2,0.2,0.2)`, `position_ = (10,10,20,0)`, `coeficients_ = (0,0,1)`
- Scene: `lightAmbientGlobal = (0.3, 0.3, 0.3)`

A continuación podemos ver una esfera (`sphere0.obj`) a la que se le ha aplicado el sombreado de Gouraud.

![Gouraud](./resources/screenshots/gouraud_ejemplo.PNG)

En esta imagen se puede apreciar el uso del sompreado de Phong en una esfera (`sphere0.obj`). Pese a que pueden ser poco perceptible sus diferencias
se puede observar que para Phong la luz que visualizamos se escuentra más suavizada, este es un resultado que cabría esperar ya que al calcular las normales para cada pixel en lugar de para cada vértice de la imagen el resultado será más 'natural' en lugar de tener una apariencia más pixelada.

Para poder comparar las imágenes obtenidas de estas dos técnicas lo mejor posible es recomendable poner la componente especular de la luz a (1,1,1).

![Phong](./resources/screenshots/phong_ejemplo.PNG)

Por último, podemos visualizar como el sombreado de Toon en una esfera (`sphere0.obj`) proporciona un efecto más plano del sombreado de ésta haciéndola parecer menos realista.

![Toon](./resources/screenshots/toon_ejemplo.PNG)

Cabe destacar la consulta de [Simulación Gouraud/Phong](https://rabbid76.github.io/graphics-snippets/html/stackoverflow/gouraud_phong.html) para visualizar diversas figuras con las distintas técnicas de shaders para comparar los imágenes obtenidas.

*(NOTA: Per a cada pas de l'enunciat (del 1 al 6), incloure captures de pantalla de les proves que heu fet per a demostrar la funcionalitat de la vostra pràctica amb explicacions de la seva configuració i com les heu aconseguides)*

*(NOTA2: Breu explicació, si cal, de com replicar els vostres resultats)*

**Additional Information**

*(NOTA: Hores de dedicació i problemes que heu tingut fent la pràctica)*
