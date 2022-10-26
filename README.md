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
- Historie hledaných videí
- Bez reklam

# Odkazy ke stažení

- [Stáhnout instalačku](https://github.com/RxiPland/y2mate_desktop/releases/download/v1.7.2/y2mate_setup.exe) exe (win64) ```md5: ce7a7aeae932112721a6a52dc2e1ebfb```

- [Stáhnout zip](https://github.com/RxiPland/y2mate_desktop/releases/download/v1.7.2/y2mate.zip) (win64) ```md5: 0fe324a6de84f2b4e42e119b0bfcaebe```

# Náhled
![1](https://user-images.githubusercontent.com/82058894/197359556-41ac0e91-b4d3-4119-91ee-dfdcdb485f85.png)
#
![2](https://user-images.githubusercontent.com/82058894/197359564-329a3cbd-24f5-462e-af35-08fab10cd48d.png)
#
![3](https://user-images.githubusercontent.com/82058894/197996025-b3d64a86-8484-4bbe-84e5-51fda1741fe5.png)


# Poznámky

- Program byl vytvořen v [QT creatoru](https://www.qt.io/product/development-tools)
- Verze knihovny: QT6
- Při komunikaci v requestech je použit user-agent chromu
- Pro zjišťování nové verze programu je použito github API
- Pokud se soubor stáhne jako .webm - je to chyba na straně y2mate.com
