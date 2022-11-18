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
- Možnost upravit videu čas začátku a konce ([FFmpeg](https://ffmpeg.org/))
- Možnost konverze do .OGG nebo i .WAV
- Aplikace je kompletně v češtině
- Přehledné/jednoduché prostředí
- Historie hledaných videí
- Bez reklam

# Odkazy ke stažení

- [Stáhnout instalačku](https://github.com/RxiPland/y2mate_desktop/releases/download/v1.8.0/y2mate_setup.exe) exe (win64) ```md5: 13c52b490c9d50d66405a8a7a11134a7```

- [Stáhnout zip](https://github.com/RxiPland/y2mate_desktop/releases/download/v1.8.0/y2mate.zip) (win64) ```md5: e29f31d3ae57074902a077ebd03176cd```

# Náhled
![1](https://user-images.githubusercontent.com/82058894/198419676-acdc73e0-9a34-467e-b4d2-7be3fc5de40e.png)
##
![2](https://user-images.githubusercontent.com/82058894/198419690-752736d8-5b31-4596-bab3-70f91ecbdd07.png)
##
![3](https://user-images.githubusercontent.com/82058894/202700249-bad83c53-10bc-493c-b9b2-fb33771e2cbc.png)
##
![4](https://user-images.githubusercontent.com/82058894/202700294-26342c9d-8dd7-42e1-9753-0335c01d0b9e.png)

# Poznámky

- Program byl vytvořen v [QT creatoru](https://www.qt.io/product/development-tools)
- Verze knihovny: QT6
- Při komunikaci v requestech je použit user-agent chromu
- Pro zjišťování nové verze programu je použito github API
- Pokud se soubor stáhne jako .webm, je chyba pouze v pojmenování, nikoliv formátu
- FFmpeg.exe je stahován z tohoho githubu z releasu v1.8.0 (poté je umístěn {složka programu}/tools/ffmpeg.exe)
