# 🎮 Hub IR – Télécommande universelle Arduino & PC

## 📌 Description du projet

**Hub IR** est une application C++ couplée à un Arduino recevant des signaux infrarouges (IR), permettant de déclencher des actions personnalisées sur un ordinateur.

- Le microcontrôleur envoie un code IR via le port série.
- L'application desktop reçoit ce code et déclenche une action préconfigurée (clavier, souris, site web...).
- Une interface graphique (via Raylib) permet de configurer facilement chaque code IR avec une action.

---

## 📁 Organisation du projet

```
hub_ir/
├── include/                 # Fichiers d'en-tête (headers)
│   ├── Core.hpp
│   ├── Config.hpp
│   └── WindowsSerialBackend.hpp / LinuxSerialBackend.hpp
├── src/                    # Code source principal
│   ├── Core.cpp            # Cœur de l'application
│   ├── Config.cpp          # Lecture/écriture du JSON de config + actions
│   ├── main.cpp            # Point d'entrée de l'application
│   └── UI/                 # Interface graphique
│       ├── Ui.cpp
│       ├── ButtonFactory.cpp
│       └── components/
├── Platform.hpp            # Inclusion conditionnelle (Windows / Linux)
├── config/                 # Fichier JSON de configuration
├── Makefile / Dockerfile   # Compilation standard ou croisée
└── README.md               # Cette documentation
```

---

## ⚙️ Compilation

### ✅ Linux (native)

```bash
make
./hub_ir
```

### ✅ Windows (depuis Linux via Docker + MinGW)

```bash
make build  # build l'image Docker
make ex     # génère hub_ir.exe via Docker
```

> ⚠️ Nécessite Raylib Windows précompilé (headers et `.a`) dans `/opt/raylib/raylib-5.5_win64_mingw-w64/`

---

## 🖥️ Dépendances

- [Raylib](https://www.raylib.com/)
- Linux : `xdotool`, `amixer`
- Windows : `ShellExecuteA`, `keybd_event`, etc.
- Arduino avec capteur infrarouge : envoie via Serial les codes IR reçus

---

## 🔧 Utilisation

### 1. **Lancer l'application**
- Elle écoute automatiquement le port série et affiche l'interface.

### 2. **Configurer les signaux IR**
- Appuyez sur un bouton de votre télécommande.
- Le signal est reçu une seule fois.
- Attribuez-lui une action via la GUI.

### 3. **Sauvegarde automatique**
- Les actions sont stockées dans un fichier JSON (`config/default_config.json`).

---

## 🧠 Fonctionnalités

- 🖱️ Simuler clic souris
- 🎹 Simuler combinaison de touches (Ctrl+T, espace…)
- 🌐 Ouvrir des sites web (YouTube, Discord…)
- 🔊 Gérer le son (volume +/-, mute)
- 🧠 Cross-platform (Windows & Linux)
- 🧱 Interface simple pour attribuer les actions

---

## 🐞 Débogage

- Les messages sont loggés dans le terminal.
- Le programme affiche tous les signaux reçus, même inconnus.
- Si un signal est inconnu, il peut être attribué manuellement.

---

## ❓FAQ

**Q : Que faire si l'application ne reçoit rien ?**  
R : Vérifiez le bon port série dans `WindowsSerialBackend` ou `LinuxSerialBackend`.

**Q : Puis-je modifier le fichier JSON à la main ?**  
R : Oui, mais faites attention à sa validité (utilise le format `clé` → `action`).

---

## 👨‍💻 Pour les développeurs

Pour ajouter une nouvelle action :
1. Modifier la classe `Config` (`pressKey`, `openSite`, etc.).
2. Ajouter l’action dans la map `_actions` dans `Core.cpp`.

---

## 📜 Licence

Projet réalisé dans le cadre d’un projet Epitech, librement modifiable à usage personnel ou éducatif.
