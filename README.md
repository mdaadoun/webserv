# WEBSERV

> Le projet consiste à développer un serveur HTTP en utilisant uniquement les fonctionnalités de base de la programmation réseau avec les sockets.  
> Pour résumer le travail consiste à :
> * Analyser et valider le fichier de configuration
> * Établir une connexion via un socket pour écouter les requêtes
> * Implémenter le protocole HTTP et sa structure de requête/réponse
>   * Parser et traiter les requêtes HTTP.
>   * Construire réponses nécessaires pour délivrer le résultat.
> * (Optionnel) gérer les cookies et la gestion de session, ainsi que différents CGI.

## Compilation et utilisation

### Compilation

```
make OU make all
```
Pour compiler le projet et le main de test unitaires

```
make serv
```
Pour compiler uniquement le projet (le serveur)

```
make test
```
Pour compiler uniquement le main de tests unitaires

### Utilisation

```
./webserv [CONFIG_FILE]
```
Pour utiliser le serveur

```
./webserv_test
```
Pour utiliser le programme de tests unitaires


## Sommaire

> Ci dessous, en plus détaillé, voir les sections:  
**1) Les étapes pour la partie obligatoire**  
**2) Le fichier de configuration**  
**3) Les étapes pour la partie bonus**  
**4) Le testeur python**  
**5) Normes C++98 de l'équipe**  
**6) Git**

### 1) Les étapes pour la partie obligatoire

1. **Mise en place de l'environnement de développement** : installation des outils nécessaires et configuration des paramètres de développement.

2. **Comprendre le fonctionnement des sockets** : étudier les concepts de base des sockets, les protocoles de communication réseau et les spécifications HTTP.

3. **Mise en place de l'infrastructure de base**:implémentation d'un serveur HTTP de base qui peut recevoir et traiter les requêtes HTTP simples.
    * Configurer les sockets en mode bloquant pour comprendre les bases de la communication réseau.
    * Mettre en place un serveur HTTP qui peut gérer une requête et renvoyer une réponse basique.
    * Analyse de la requête et construction de la réponse.

4. **Analyse des requêtes** : implémentation de la logique pour analyser les requêtes HTTP et construire les réponses correspondantes.
    * Étudier les règles HTTP (https://www.rfc-editor.org/rfc/rfc9112.html).
    * Décoder les requêtes HTTP et construire des réponses correspondantes en utilisant le format correct et les codes d'état HTTP appropriés.

5. **Mise en œuvre de la gestion de la file d'attente** : implémentation de la logique pour gérer les requêtes en attente dans une file d'attente.
    * Passage aux sockets en mode non bloquant et implémentation de la logique de multiplexage (utiliser poll(), epoll, kqueue ou select).
    * L'objectif est de contrôler à la fois les opérations de lecture et d'écriture pour éviter les blocages.
    * Éviter d'utiliser read/recv ou write/send sans passer par poll() (ou équivalent).
    * Utiliser les macros FD_SET, FD_CLR, FD_ISSET, FD_ZERO pour contrôler les sockets.
    * Assurer que les requêtes ne bloquent jamais indéfiniment.

6. **Support des fichiers statiques** : implémentation de la logique pour traiter les requêtes pour les fichiers statiques (tels que les images, les feuilles de style, etc.).
    * Mettre en place un fichier de configuration qui peut être passé en argument ou utiliser un chemin par défaut.

7. **Support des scripts CGI** : implémentation de la logique pour exécuter des scripts CGI et fournir leurs résultats à l'utilisateur.
    * Ajouter la prise en charge de CGI pour gérer les scripts et les programmes externes.

8. **Prise en charge des différentes méthodes HTTP** : implémentation des logiques pour prendre en charge les méthodes HTTP telles que GET, POST, DELETE, etc. 
   * L'objectif est d'obtenir une gestion complète des requêtes.

9. **Mise en place d'un système de configuration** : implémentation de la logique pour lire et utiliser un fichier de configuration pour les paramètres de configuration du serveur.

10. **Tests et débogage** : effectuer des tests pour vérifier la conformité aux spécifications et corriger les erreurs éventuelles.
    * Le testeur python est utilisé principalement pour comparer les résultats de webserv avec le serveur Nginx.
    * Compatibilité avec les navigateurs web courants.
    * Testeurs fournis par le projet.

11. **Documentation** : documenter/commenter le code pour une meilleure compréhension du projet.

* Autres considérations du sujet:
    * Utiliser des pages d'erreur par défaut si nécessaire.
    * Interdiction d'utiliser fork pour autre chose que CGI.
    * Capacité à servir des sites web entièrement statiques.
    * Possibilité de télécharger des fichiers pour le client. (pdf ?)
    * Écouter sur plusieurs ports en fonction de la configuration.
    * Stress testing pour garantir la disponibilité du serveur à tout moment. (voir Siege)

## 2) Le fichier de configuration :

1. Définir le port et l'hôte pour chaque "serveur".
2. Configurer les noms de serveur si nécessaire.
3. Définir le premier serveur pour chaque host:port en tant que serveur par défaut pour cet host:port.
4. Configurer les pages d'erreur par défaut.
5. Limiter la taille du corps des clients.
6. Configurer les routes en utilisant les règles suivantes:
    * Définir les méthodes HTTP acceptées pour chaque route.
    * Configurer la redirection HTTP.
    * Définir le répertoire ou le fichier source pour la requête.
    * Activer ou désactiver le listing des répertoires.
    * Définir un fichier par défaut pour les requêtes de répertoire.
    * Configurer l'exécution CGI pour les extensions de fichier spécifiques (comme .php).
    * Configurer l'acceptation de fichiers téléchargés et leur emplacement d'enregistrement.
7. Pour les requêtes fragmentées, dé-fragmenter la requête et attendre EOF comme fin du corps.
8. Pour la sortie du CGI, attendre EOF pour signifier la fin des données renvoyées si aucun content_length n'est renvoyé.
9. Exécuter le CGI avec le fichier demandé en premier argument et dans le bon répertoire pour l'accès aux fichiers de chemin relatif.
10. Fonctionner avec un seul type de CGI (Python!).
11. Fournir des fichiers de configuration et des fichiers de base par défaut pour tester et démontrer les fonctionnalités. (Ameliorer en consequence le generateur de fichiers du testeur Python)

## 3) Les étapes pour la partie bonus

1. Implémenter la gestion des cookies :
    * Lire les en-têtes de requête pour trouver les cookies envoyés par le client.
    * Stocker les informations de session associées à un cookie sur le serveur.
    * Ajouter les informations de session à chaque réponse envoyée au client en utilisant les en-têtes "Set-Cookie".

2. Implémenter la gestion des sessions :
    * Associer les informations de session à une identité utilisateur.
    * Mettre à jour les informations de session pour chaque requête entrante en utilisant les informations de cookie.

3. Gérer plusieurs CGI :
    * Écrire un gestionnaire de processus pour exécuter plusieurs CGI simultanément.
    * Implémenter la communication entre les processus CGI et le serveur web pour échanger les données d'entrée et de sortie.
    * Configurer le serveur web pour appeler le gestionnaire de processus pour exécuter un CGI spécifique en fonction de l'extension du fichier demandé.

4. Préparer des exemples de gestion de session et de cookie rapides pour tester et démontrer les fonctionnalités implémentées.

## 4) Le testeur python

```
  dans un environnement virtuel
  > python3 -m venv venv
  > source venv/bin/activate
  > pip3 install -r requirements.txt
  > python3 run.py
  
  ou alors simplement
  > pip3 install -r requirements.txt
  > chmod +x run.py
  > ./run.py
```
* Il doit afficher de l'aide pour l'utilisation du testeur.
* Le testeur peut être utilisé pour des vérifications rapides pendant le développement.
* En fin de compte, le serveur doit être testé avec un navigateur et la différence avec un serveur Nginx doit être vérifiée.


## 5) Normes C++98 de l'équipe

### Structure :
>./Makefile  (setting)
>./config.ini (config files)
./src/main.cpp (for *.cpp)  
./src/ft_utils.cpp (functions without class)  
./inc/Webserv.class.hpp (for *.hpp)  
./inc/tpp/Webserv.template.tpp (for template)  
./inc/ipp/Webserv.template.tpp (for interface)  

### Noms de fonctions :
>**ft_function_name**: global function (utils...)  
**fs_function_name**: static function (same file)  
**dg_function_name**: debug/test function (from debug.hpp)

### Noms de classes:
> ClassName
pour les fichiers
> ClassName.class.hpp 

## Methods names:
> getName

## Class variables:
> _private_attribute
>
> public_attribute
>
> g_global_attribute

## Struct and enum + typedef
```
e_enum
s_struct
t_typedef
```

## const everywhere
```
<type> const& <function/attribute> const
```
## tab == 4 espaces

## Comment formating
A function should be correctly commented, with brief (function purpose), param (sent parameters), return (returned value)
```c
Simple line comment:
// hello
Multiline comment:
/*
*  @brief	Default constructor of the class Socket.
*               Initialize the socket without any parameters
*  @param	void
*  @return	void
*/
Socket::Socket(void): _fd(-1) {}
```

### 6) Git

voir git flow
* Fork/Branch functionality/Pull Request/Merge on branch dev
* When ok, dev merge sur main et continuer sur dev
