Algoritmus determinizace koneèného automatu je klíèovým nástrojem v teorii formálních jazykù. Nalézá rozsáhlé praktické využití ve zpracování textu, analýze dat a v rùzných oblastech informatiky. Tím, že konvertuje nedeterministické automaty na deterministické, umožòuje efektivní analýzu jazykù, což je klíèové v kompilátorech, analýze textu, vyhledávání regulárních výrazù, øízení sítí, databázových systémech a mnoha dalších aplikacích.

Úkolem je najít deterministický koneèný automat bez zbyteèných a nedosažitelných stavù takový, aby jazyk, který pøijímá byl ekvivalentní k jazyku zadaného nedeterministického koneèného automatu s více poèáteèními stavy.

Determinizaci implementujte v podobì funkce programu v C++, jejíž signatura je: DFA determinize ( const MISNFA & nfa );. Vstupem, resp. výstupem algoritmu jsou automaty v podobì struktur MISNFA, resp. DFA reprezentující nedeterministický koneèný automat s více poè. stavy, resp. deterministický koneèný automat. Tyto struktury jsou definovány v testovacím prostøedí, viz ukázka níže. Pro zjednodušení jsou stavy definovány jako hodnoty typu int a symboly abecedy jako hodnoty typu char.

Porovnání automatù s referenèním výsledkem se provádí pøes pøevod na minimální deterministický koneèný automat. Vaše výstupy se mohou lišit (napø. v pojmenování stavù). Po pøevedení na minimální automat, které provede testovací prostøedí (tj. minimalizace není vaší starostí), však musí dát ekvivalentní automat (pojmenování stavù nehraje roli).

Je zaruèeno, že na vstupu pøijde validní nedeterministický koneèný automat s více poèáteèními stavy, tedy:

množiny stavù (MISNFA::m_States), poèáteèních stavù (MISNFA::m_InitialStates) a symbolù abecedy (MISNFA::m_Alphabet) budou neprázdné,
poèáteèní a koncové stavy z množin MISNFA::m_InitialStates a MISNFA::m_FinalStates budou také prvky množiny stavù MISNFA::m_States,
pokud nebude pro nìjaký stav q a symbol abecedy a definovaný pøechod v automatu, pak v mapì MISNFA::m_Transitions nebude ke klíèi (q, a) pøiøazená hodnota prázdná množina, ale tento klíè nebude vùbec existovat,
v mapì pøechodù MISNFA::m_Transitions se vyskytují také jen prvky, které jsou specifikovány v množinì symbolù abecedy a stavù.
Výsledný DFA musí také splòovat podmínky definice automatu, tedy musí platit to samé co výše pro MISNFA (až na zøejmé zmìny kvùli rozdílným definicím poèáteèního stavu a pøechodové funkce).

V pøípadì, že jazyk automatu je prázdný, odevzdávejte jednostavový automat nad stejnou abecedou, jako je pùvodní automat.

Odevzdávejte zdrojový soubor, který obsahuje implementaci požadované funkce determinize. Do zdrojového souboru pøidejte i další Vaše podpùrné funkce, které jsou z determinize volané. Funkce bude volaná z testovacího prostøedí, je proto dùležité pøesnì dodržet zadané rozhraní funkce. Za základ pro implementaci použijte kód z ukázky níže. V kódu chybí vyplnit funkci determinize (a pøípadné další podpùrné funkce). Ukázka obsahuje testovací funkci main, uvedené hodnoty jsou použité pøi základním testu. Všimnìte si, že vkládání hlavièkových souborù, struktur DFA a MISNFA a funkce main jsou zabalené v bloku podmínìného pøekladu (#ifdef/#endif). Prosím, ponechte bloky podmínìného pøekladu i v odevzdávaném zdrojovém souboru. Podmínìný pøeklad Vám zjednoduší práci. Pøi kompilaci na Vašem poèítaèi mùžete program normálnì spouštìt a testovat. Pøi kompilaci na Progtestu funkce main a vkládání hlavièkových souborù "zmizí", tedy nebude kolidovat s hlavièkovými soubory a funkcí main testovacího prostøedí.

Pro základ implementace mùžete využít soubor ke stažení níže v sekci Vzorová data. Tento soubor obsahuje také nìkolik základních testù, mìjte však na pamìti, že výsledky Vaší ímplementace se mohou lišit. Testy jsou nastaveny podle výsledkù, které dává jedno z referenèních øešení. Možná si je tedy budete muset upravit.

Váš program bude spouštìn v omezeném testovacím prostøedí. Je omezen dobou bìhu (limit je vidìt v logu referenèního øešení) a dále je omezena i velikost dostupné pamìti.