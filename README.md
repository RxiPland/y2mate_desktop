# y2mate Youtube downloader

- Nenáročný program na stahování videí/hudby z youtube
- Včetně videí omezených věkem
- Program využívá stránku [y2mate.com](https://www.y2mate.com/) (I'am not owner of this website!)
- Možnost sestříhat si délku videa
- Možnost konverze do audio formátů jako .OGG, .WAV nebo [.FLAC](https://cs.wikipedia.org/wiki/Free_Lossless_Audio_Codec)
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

- [Stáhnout instalačku](https://github.com/RxiPland/y2mate_desktop/releases/download/v2.2.0/y2mate_setup.exe) exe (win64) `md5: 930b795983cd089f104ac8dbc907ad6a`
- [Stáhnout zip](https://github.com/RxiPland/y2mate_desktop/releases/download/v2.2.0/y2mate.zip) (win64) `md5: 35ce109a3028fd04569db4a9dc4ae0a1`


<br/>

# Náhled
![1](https://user-images.githubusercontent.com/82058894/227725060-a657fb70-43ff-4b50-bd9e-89c1c5ef58c6.png)
##
![2](https://user-images.githubusercontent.com/82058894/227725073-b48f03c0-0bf6-4648-bd3e-f875f9171071.png)
##
![3](https://user-images.githubusercontent.com/82058894/225476745-3c9b024e-3c1b-437b-b0b9-6e3e6f8a4b0b.png)
##
![4](https://user-images.githubusercontent.com/82058894/227725085-b200b8dd-195a-4e8b-a68c-3bb78029edc0.png)

<br/>

# Beta testeři
- [Marmot](https://github.com/MarmotLand)

<br/>

# Poznámky

- Program byl vytvořen v [QT creatoru](https://www.qt.io/product/development-tools)
- Verze knihovny Qt: 6.4.3
- Při komunikaci v requestech je použit user-agent chromu
- Pro zjišťování nové verze programu je použito github API
- FFmpeg.exe je možné stáhnout z tohoto githubu z releasu v1.8.0 (poté je umístěn {složka programu}/Data/ffmpeg.exe)
- Při automatickém stahování (instalování) aktualizací se vždy stáhne instalačka (i přes to, že byl program stáhnut jako .zip)
