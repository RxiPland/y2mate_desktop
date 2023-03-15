# y2mate Youtube downloader

- Nenáročný program na stahování videí/hudby z youtube
- Včetně videí omezených věkem
- Program využívá stránku [y2mate.com](https://www.y2mate.com/) (I'am not owner of this website!)
- Možnost sestříhat si délku videa
- Možnost konverze do formátů jako .OGG nebo .WAV
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
- Aplikace je kompletně v češtině
- Přehledné/jednoduché prostředí
- Historie hledaných videí
- Bez reklam

<br/>

# Odkazy ke stažení

- Probíhá kompletní přepracování na verzi v2.x.x (nefunkčnost nižších verzí)

<br/>

# Náhled
![1](https://user-images.githubusercontent.com/82058894/204152592-f25fbae1-a79a-48af-96fa-79e3bd0e8a24.png)
##

<br/>

# Beta testeři
- [Marmot](https://github.com/MarmotLand)

<br/>

# Poznámky

- Program byl vytvořen v [QT creatoru](https://www.qt.io/product/development-tools)
- Verze knihovny Qt: 6.4.2
- Při komunikaci v requestech je použit user-agent chromu
- Pro zjišťování nové verze programu je použito github API
- FFmpeg.exe je stahován z tohoho githubu z releasu v1.8.0 (poté je umístěn {složka programu}/Data/ffmpeg.exe)
