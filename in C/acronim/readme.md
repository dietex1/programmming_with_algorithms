Úkolem je vytvořit program, který bude vyhledávat zkratky (a tím vzdá hold nesmrtelné písni Ivana Mládka - nebo snad Zdeňka Svěráka).

Program dostane hledanou zkratku -- např. FIT. Zkratka je tvořena písmeny velké abecedy (A-Z). Po zadání zkratky následují zadání problémů s vyhledáním této zkratky. Zadání problému má dvě podoby:

? N "text"
nebo 
# N "text"
V uvozovkách může být zadaný libovolný text (neobsahuje odřádkování a uvozovky) a N je celé číslo. Program se pokusí vyhledat zadanou zkratku v textu. Při vyhledávání musí v textu identifikovat písmena zkratky (nerozlišujeme malá/velká písmena), pořadí písmen v textu musí odpovídat pořadí písmen ve zkratce a do každého slova v textu lze umístit nejvýše N písmen zkratky. Tedy například pro zkratku FIT a vstup:

# 1 "Faculty of Information Technology"
lze vybrat zkratku např. těmito způsoby:
"Faculty of Information Technology"
"faculty oF Information Technology"
"Faculty of informatIon Technology"
...
ale ne například takto:
"faculTy oF Information technology"
"Faculty of InformaTion technology"
v prvním případě není zachované pořadí písmen, ve druhém pak vybíráme 2 písmena ze slova Information, ale limit je N=1 písmeno.

Obecně lze zadanou zkratku nalézt v zadaném textu několika různými způsoby. Úkolem programu je vypočítat, kolika různými způsoby lze zkratku nalézt. Pokud je zadán problém ve tvaru:

? N "text"
očekává se, že program vyhledá zkratky podle popsaných pravidel a vypíše všechny nalezené možnosti. Ve výpisu program zdůrazní písmena ze zkratky (zobrazí je jako velká) a ostatní písmena z textu zobrazí jako malá. Nakonec připojí informaci o počtu nalezených možností.
Pokud je zadán problém ve tvaru:

# N "text"
pak program opět spočte možnosti, ale nevypisuje pozice jednotlivých nalezených zkratek. Pouze vypíše počet nalezených možností, jak lze zkratky do textu umístit. Navíc tyto počty určí pro limit 1, 2, 3, ..., N písmen zkratky maximálně umístěných do jednoho slova textu.
Vstup je zpracováván po řádkách. Na první řádce je zadaná hledaná zkratka, řádka nesmí obsahovat žádné další znaky navíc. Zkratka musí být zadaná velkými písmeny. Její délka není obecně omezená. Po zadání zkratky následuje zadání jednotlivých problémů -- textů k hledání. Formát problému je popsaný výše. Každý problém musí být zadán na jedné řádce. Program zpracovává problémy ze vstupu, dokud nedosáhne konce vstupu (EOF).

Výstupem programu je text s nalezenými pozicemi písmen zkratky a informace o počtu možností, kterými lze zkratku to textu umístit. Při výpisu textu s pozicemi písmen zkratky nezáleží na pořadí vypisovaných řádek. Formátování výstupu je zřejmé z ukázky níže.

Pokud je vstup neplatný, program to musí detekovat a zobrazit chybové hlášení. Chybové hlášení zobrazujte na standardní výstup (ne na chybový výstup). Za chybu považujte:

první řádka neobsahovala zkratku, zkratka byla prázdná (nulové délky) nebo se ve zkratce objevily jiné znaky než velká písmena,
nebyl rozpoznán problém k vyřešení (# a ?),
číslo N v zadání problému chybí, není platné, je nulové nebo záporné,
prohledávaný text není umístěn do uvozovek nebo nějaká uvozovka chybí.
Ukázka práce programu:
Zkratka:
FIT
Problemy:
? 1 "Faculty of Information Technology"
"Faculty of Information Technology"
"Faculty of informatIon Technology"
"faculty oF Information Technology"
"faculty oF informatIon Technology"
> 4
? 2 "Faculty of Information Technology"
"Faculty of InformaTion technology"
"Faculty of Information Technology"
"Faculty of informatIon Technology"
"faculty oF InformaTion technology"
"faculty oF Information Technology"
"faculty oF informatIon Technology"
"faculty of inFormatIon Technology"
> 7
? 2 "FIT"
> 0
? 3 "FIT"
"FIT"
> 1
? 2   "Fibonacci   test"  
"FIbonacci   Test"
"FIbonacci   tesT"
"FibonaccI   Test"
"FibonaccI   tesT"
> 4
? 2   "  Fibonacci   test   "  
"  FIbonacci   Test   "
"  FIbonacci   tesT   "
"  FibonaccI   Test   "
"  FibonaccI   tesT   "
> 4
? 3 "Flux field inspection and particle affiliation department"
"Flux fIeld inspecTion and particle affiliation department"
"Flux fIeld inspection and parTicle affiliation department"
"Flux fIeld inspection and particle affiliaTion department"
"Flux fIeld inspection and particle affiliation deparTment"
"Flux fIeld inspection and particle affiliation departmenT"
"Flux field InspecTion and particle affiliation department"
"Flux field Inspection and parTicle affiliation department"
"Flux field Inspection and particle affiliaTion department"
"Flux field Inspection and particle affiliation deparTment"
"Flux field Inspection and particle affiliation departmenT"
"Flux field inspectIon and parTicle affiliation department"
"Flux field inspectIon and particle affiliaTion department"
"Flux field inspectIon and particle affiliation deparTment"
"Flux field inspectIon and particle affiliation departmenT"
"Flux field inspection and partIcle affiliaTion department"
"Flux field inspection and partIcle affiliation deparTment"
"Flux field inspection and partIcle affiliation departmenT"
"Flux field inspection and particle affIliaTion department"
"Flux field inspection and particle affIliation deparTment"
"Flux field inspection and particle affIliation departmenT"
"Flux field inspection and particle affilIaTion department"
"Flux field inspection and particle affilIation deparTment"
"Flux field inspection and particle affilIation departmenT"
"Flux field inspection and particle affiliatIon deparTment"
"Flux field inspection and particle affiliatIon departmenT"
"flux FIeld inspecTion and particle affiliation department"
"flux FIeld inspection and parTicle affiliation department"
"flux FIeld inspection and particle affiliaTion department"
"flux FIeld inspection and particle affiliation deparTment"
"flux FIeld inspection and particle affiliation departmenT"
"flux Field InspecTion and particle affiliation department"
"flux Field Inspection and parTicle affiliation department"
"flux Field Inspection and particle affiliaTion department"
"flux Field Inspection and particle affiliation deparTment"
"flux Field Inspection and particle affiliation departmenT"
"flux Field inspectIon and parTicle affiliation department"
"flux Field inspectIon and particle affiliaTion department"
"flux Field inspectIon and particle affiliation deparTment"
"flux Field inspectIon and particle affiliation departmenT"
"flux Field inspection and partIcle affiliaTion department"
"flux Field inspection and partIcle affiliation deparTment"
"flux Field inspection and partIcle affiliation departmenT"
"flux Field inspection and particle affIliaTion department"
"flux Field inspection and particle affIliation deparTment"
"flux Field inspection and particle affIliation departmenT"
"flux Field inspection and particle affilIaTion department"
"flux Field inspection and particle affilIation deparTment"
"flux Field inspection and particle affilIation departmenT"
"flux Field inspection and particle affiliatIon deparTment"
"flux Field inspection and particle affiliatIon departmenT"
"flux field inspection and particle aFfIliaTion department"
"flux field inspection and particle aFfIliation deparTment"
"flux field inspection and particle aFfIliation departmenT"
"flux field inspection and particle aFfilIaTion department"
"flux field inspection and particle aFfilIation deparTment"
"flux field inspection and particle aFfilIation departmenT"
"flux field inspection and particle aFfiliatIon deparTment"
"flux field inspection and particle aFfiliatIon departmenT"
"flux field inspection and particle afFIliaTion department"
"flux field inspection and particle afFIliation deparTment"
"flux field inspection and particle afFIliation departmenT"
"flux field inspection and particle afFilIaTion department"
"flux field inspection and particle afFilIation deparTment"
"flux field inspection and particle afFilIation departmenT"
"flux field inspection and particle afFiliatIon deparTment"
"flux field inspection and particle afFiliatIon departmenT"
> 66
# 4 "figure fits the first filter of floating firmware in the field width transistor to instance"
> limit 1: 238
> limit 2: 321
> limit 3: 324
> limit 4: 324
# 1 "Stay fit!"
> limit 1: 0
#
Nespravny vstup.
Zkratka:
Hello
Nespravny vstup.
