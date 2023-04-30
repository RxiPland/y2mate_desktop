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

- [Stáhnout instalačku](https://github.com/RxiPland/y2mate_desktop/releases/download/v2.2.5/y2mate_setup.exe) exe (win64) `md5: 37a2bcd9abaa31d0207540860368e6cc`
- [Stáhnout zip](https://github.com/RxiPland/y2mate_desktop/releases/download/v2.2.5/y2mate.zip) (win64) `md5: 6af716e258a04b884c7902ceabfa8a3d`


<br/>

# Náhled
![1](https://user-images.githubusercontent.com/82058894/235348520-e9a23985-2f50-42f5-9266-7b60deac006f.png)
##
![2](https://user-images.githubusercontent.com/82058894/227725073-b48f03c0-0bf6-4648-bd3e-f875f9171071.png)
##
![3](https://user-images.githubusercontent.com/82058894/225476745-3c9b024e-3c1b-437b-b0b9-6e3e6f8a4b0b.png)
##
![4](https://user-images.githubusercontent.com/82058894/235348516-ef8511f9-a42b-4908-910e-88ffe532b364.png)

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
- Každá konverze videa přes FFmpeg o trochu sníží kvalitu (bitrate), kvůli re-encodingu
