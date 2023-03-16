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

- [Stáhnout instalačku](https://github.com/RxiPland/y2mate_desktop/releases/download/v2.0.0/y2mate_setup.exe) exe (win64) `md5: c671362d348dd180a97c2d06b07243fe`
- [Stáhnout zip](https://github.com/RxiPland/y2mate_desktop/releases/download/v2.0.0/y2mate.zip) (win64) `md5: 2b40d4a5fb361a91603eed8f2a7ddc2e`


<br/>

# Náhled
![1](https://user-images.githubusercontent.com/82058894/225476708-53543cef-ffbd-40cd-95f1-556ec382208f.png)
##
![3](https://user-images.githubusercontent.com/82058894/225476735-3afd7a9f-4ce0-4eab-8404-3d45a4ff1faf.png)
##
![4](https://user-images.githubusercontent.com/82058894/225476745-3c9b024e-3c1b-437b-b0b9-6e3e6f8a4b0b.png)
##
![2](https://user-images.githubusercontent.com/82058894/225476721-b1a4583c-81f2-452d-91c8-4446158b5806.png)

<br/>

# Beta testeři
- [Marmot](https://github.com/MarmotLand)

<br/>

# Poznámky

- Program byl vytvořen v [QT creatoru](https://www.qt.io/product/development-tools)
- Verze knihovny Qt: 6.4.2
- Při komunikaci v requestech je použit user-agent chromu
- Pro zjišťování nové verze programu je použito github API
- FFmpeg.exe je možné stáhnout z tohoho githubu z releasu v1.8.0 (poté je umístěn {složka programu}/Data/ffmpeg.exe)
