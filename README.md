# y2mate Youtube downloader

- Nenáročný program na stahování videí/hudby z youtube
- Včetně videí omezených věkem
- Program využívá stránku [y2mate.com](https://www.y2mate.com/)
#
- Video kvalita maximálně 1080p
- Kvalita zvuku maximálně 320kbps

### Výhody oproti webové verzi y2mate
- Stažený soubor neobsahuje v názvu:
  - y2mate watermark
  - bitrate (kvalitu)
  - dvojité mezery
- Aplikace je kompletně v češtině
- Přehledné/jednoduché prostředí
- Historie stažených videí
- Bez reklam

# Odkazy ke stažení

- [Stáhnout instalačku](https://github.com/RxiPland/y2mate_desktop/releases/download/v1.7.0/y2mate_setup.exe) exe (win64) ```md5: 94374b980c775c99d69d36debbf9b4d2```

- [Stáhnout zip](https://github.com/RxiPland/y2mate_desktop/releases/download/v1.7.0/y2mate.zip) (win64) ```md5: 37edce47cb744109ef397d2ff0f79773```

# Náhled
![1](https://user-images.githubusercontent.com/82058894/192157051-f4f3fecc-f9dc-4ac6-95d1-d9bc6a12cec0.png)
#
![2](https://user-images.githubusercontent.com/82058894/192157057-07b44d08-cc64-4b9e-8e44-20a3ff25befd.png)
#
![3](https://user-images.githubusercontent.com/82058894/197247283-83e8dff9-7482-4e9b-b29e-eba5945d8586.png)


# Poznámky

- Program byl vytvořen v [QT creatoru](https://www.qt.io/product/development-tools)
- Verze knihovny: QT6
- Při komunikaci v requestech je použit user-agent chromu
- Pro zjišťování nové verze programu je použito github API
- Pokud se soubor stáhne jako .webm - je to chyba na straně y2mate.com
