# y2mate Youtube downloader

- Nenáročný program na stahování videí/hudby z youtube
- Včetně videí omezených věkem
- Program využívá stránku [y2mate.com](https://www.y2mate.com/)
- Možnost si sestříhat délku videa
#
- Video kvalita maximálně 1080p
- Kvalita zvuku maximálně 320kbps

### Výhody oproti webové verzi y2mate
- Stažený soubor neobsahuje v názvu:
  - y2mate watermark
  - bitrate (kvalitu)
  - dvojité mezery
  - mezery na začátku a konci
- Možnost upravit videu čas začátku a konce ([FFmpeg](https://ffmpeg.org/))
- Možnost konverze do .OGG nebo i .WAV
- Aplikace je kompletně v češtině
- Přehledné/jednoduché prostředí
- Historie hledaných videí
- Bez reklam

# Odkazy ke stažení

- [Stáhnout instalačku](https://github.com/RxiPland/y2mate_desktop/releases/download/v1.8.3/y2mate_setup.exe) exe (win64) ```md5: cad156228ce76815f61336b8a1193720```

- [Stáhnout zip](https://github.com/RxiPland/y2mate_desktop/releases/download/v1.8.3/y2mate.zip) (win64) ```md5: 7e73b1c69f789c7828900e950c98539f```

# Náhled
![1](https://user-images.githubusercontent.com/82058894/204152592-f25fbae1-a79a-48af-96fa-79e3bd0e8a24.png)
##
![2](https://user-images.githubusercontent.com/82058894/204152598-60c0d116-b849-42d8-a469-3ae018f6c3b8.png)
##
![3](https://user-images.githubusercontent.com/82058894/204152600-84f66721-0a96-40a1-8405-3c0c4021cf37.png)
##
![4](https://user-images.githubusercontent.com/82058894/206873512-f93d4495-3ff9-44b2-a4d4-3d8321be3cea.png)

# Poznámky

- Program byl vytvořen v [QT creatoru](https://www.qt.io/product/development-tools)
- Verze knihovny: QT6
- Při komunikaci v requestech je použit user-agent chromu
- Pro zjišťování nové verze programu je použito github API
- FFmpeg.exe je stahován z tohoho githubu z releasu v1.8.0 (poté je umístěn {složka programu}/tools/ffmpeg.exe)
