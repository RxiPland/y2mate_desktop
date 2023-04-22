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

- [Stáhnout instalačku](https://github.com/RxiPland/y2mate_desktop/releases/download/v2.2.2/y2mate_setup.exe) exe (win64) `md5: e67f230b8f599fc9048edb13c7065f0c`
- [Stáhnout zip](https://github.com/RxiPland/y2mate_desktop/releases/download/v2.2.2/y2mate.zip) (win64) `md5: 2e4c46c865f9be7dd0b2dcb84bdf673e`


<br/>

# Náhled
![1](https://user-images.githubusercontent.com/82058894/233805766-6614355f-6766-4aef-b066-5621a1197e7c.png)
##
![2](https://user-images.githubusercontent.com/82058894/227725073-b48f03c0-0bf6-4648-bd3e-f875f9171071.png)
##
![3](https://user-images.githubusercontent.com/82058894/225476745-3c9b024e-3c1b-437b-b0b9-6e3e6f8a4b0b.png)
##
![4](https://user-images.githubusercontent.com/82058894/233805769-234e5849-5d6d-4a49-b44f-0af4e77d4381.png)

<br/>

# Beta testeři
- [Marmot](https://github.com/MarmotLand)

<br/>

# Poznámky

- Program byl vytvořen v [QT creatoru](https://www.qt.io/product/development-tools)
- Verze knihovny Qt: 6.5.0
- Při komunikaci v requestech je použit user-agent chromu
- Pro zjišťování nové verze programu je použito github API
- FFmpeg.exe je možné stáhnout z tohoto githubu z releasu v1.8.0 (poté je umístěn {složka programu}/Data/ffmpeg.exe)
- Při automatickém stahování (instalování) aktualizací se vždy stáhne instalačka (i přes to, že byl program stáhnut jako .zip)
