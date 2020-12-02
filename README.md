# CESI-POO
The second CESI Project of POO


## Test fonctionnel

Dans ce test fonctionnel nous allons démontrer les fonctionnalités du logiciel en réalisant les actions suivantes :

- Créer un client
- Créer un personnel
- Créer un Article
- Créer une commande

### Créer un client

- Lancer le logiciel si non lancé
- Se rendre sur l&#39;onglet « Customer »
- Remplir le formulaire sur la droite avec toutes les informations personnelles du client telles que :
  - Firstname : Valentin
  - Lastname : Dupont
  - Birth date : 14/08/1985

  - Delivery address
    - Address line : 18 chemin Cousteau
    - City : Bosdarros
    - Postal code : 64720

  - Billing address
    - Address line : 18 chemin Cousteau
    - City : Bosdarros
    - Postal code : 64720

- Valider la saisie avec le bouton « Add Customer »
- Le client apparaît ensuite dans le tableau à gauche avec les données saisies

### Créer un personnel

- Lancer le logiciel si non lancé
- Se rendre sur l&#39;onglet « Satff »
- Remplir le formulaire sur la droite avec toutes les informations personnelles du personnel telles que :

  - Firstname : René
  - Lastname : Mèlebourd
  - Hire date : 15/09/2015

  - Address
    - Address line : 24 chemin de la paine
    - City : Idron

    - Postal code : 64320

- Valider la saisie avec le bouton « Add Staff »
- Le personnel apparaît ensuite dans le tableau à gauche avec les données saisies

### Créer un article

- Lancer le logiciel si non lancé
- Se rendre sur l&#39;onglet « Item »
- Remplir le formulaire sur la droite avec toutes les informations de l&#39;article telles que :

  - Reference : IC00500MH
  - Name : Bobine 500mH
  - Resuply threshold : 20

  - Quantity : 250
  - Price HT : 0,45
  - VAT : 0,2

- Valider la saisie avec le bouton « Add Item »
- L&#39;article apparaît ensuite dans le tableau à gauche avec les données saisies

### Crée une commande

- Lancer le logiciel si non lancé
- Se rendre sur l&#39;onglet « Order »

- Cliquer sur « Reset Order » pour actualiser les articles précédemment insérés

- Se rendre sur l&#39;onglet « Customer »

- Choisir un client pour effectuer la commande : sur la ligne « Valentin Dupont » cliquer sur « Do Order »

- Se rendre sur l&#39;onglet « Staff »

- Choisir un personnel pour effectuer la commande : sur la ligne « René Melebourd » cliquer sur « Do Order »

- Se rendre sur l&#39;onglet « Order »
- Dans la rubrique « Add Item to order » sélectionner l&#39;article « Bobine 500mH », entrer quantité : 8 et Commercial Discount : 0.3
- Cliquer sur « Calcul total » en bas
- Dans la rubrique « Add Payment to order » choisir un moyen de payement : « Coin », puis le montant correspondant au total dans la case « Amount »

- Cliquer sur « Calcul total » en bas, si le payement est complété, « Left To Pay » passe à 0
- Entrer une date d&#39;estimation de la livraison : « 24/12/2020 »
- Cliquer sur « Add Order » pour valider la commande