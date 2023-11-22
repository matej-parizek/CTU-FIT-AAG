Algoritmus determinizace kone�n�ho automatu je kl��ov�m n�strojem v teorii form�ln�ch jazyk�. Nal�z� rozs�hl� praktick� vyu�it� ve zpracov�n� textu, anal�ze dat a v r�zn�ch oblastech informatiky. T�m, �e konvertuje nedeterministick� automaty na deterministick�, umo��uje efektivn� anal�zu jazyk�, co� je kl��ov� v kompil�torech, anal�ze textu, vyhled�v�n� regul�rn�ch v�raz�, ��zen� s�t�, datab�zov�ch syst�mech a mnoha dal��ch aplikac�ch.

�kolem je naj�t deterministick� kone�n� automat bez zbyte�n�ch a nedosa�iteln�ch stav� takov�, aby jazyk, kter� p�ij�m� byl ekvivalentn� k jazyku zadan�ho nedeterministick�ho kone�n�ho automatu s v�ce po��te�n�mi stavy.

Determinizaci implementujte v podob� funkce programu v C++, jej� signatura je: DFA determinize ( const MISNFA & nfa );. Vstupem, resp. v�stupem algoritmu jsou automaty v podob� struktur MISNFA, resp. DFA reprezentuj�c� nedeterministick� kone�n� automat s v�ce po�. stavy, resp. deterministick� kone�n� automat. Tyto struktury jsou definov�ny v testovac�m prost�ed�, viz uk�zka n�e. Pro zjednodu�en� jsou stavy definov�ny jako hodnoty typu int a symboly abecedy jako hodnoty typu char.

Porovn�n� automat� s referen�n�m v�sledkem se prov�d� p�es p�evod na minim�ln� deterministick� kone�n� automat. Va�e v�stupy se mohou li�it (nap�. v pojmenov�n� stav�). Po p�eveden� na minim�ln� automat, kter� provede testovac� prost�ed� (tj. minimalizace nen� va�� starost�), v�ak mus� d�t ekvivalentn� automat (pojmenov�n� stav� nehraje roli).

Je zaru�eno, �e na vstupu p�ijde validn� nedeterministick� kone�n� automat s v�ce po��te�n�mi stavy, tedy:

mno�iny stav� (MISNFA::m_States), po��te�n�ch stav� (MISNFA::m_InitialStates) a symbol� abecedy (MISNFA::m_Alphabet) budou nepr�zdn�,
po��te�n� a koncov� stavy z mno�in MISNFA::m_InitialStates a MISNFA::m_FinalStates budou tak� prvky mno�iny stav� MISNFA::m_States,
pokud nebude pro n�jak� stav q a symbol abecedy a definovan� p�echod v automatu, pak v map� MISNFA::m_Transitions nebude ke kl��i (q, a) p�i�azen� hodnota pr�zdn� mno�ina, ale tento kl�� nebude v�bec existovat,
v map� p�echod� MISNFA::m_Transitions se vyskytuj� tak� jen prvky, kter� jsou specifikov�ny v mno�in� symbol� abecedy a stav�.
V�sledn� DFA mus� tak� spl�ovat podm�nky definice automatu, tedy mus� platit to sam� co v��e pro MISNFA (a� na z�ejm� zm�ny kv�li rozd�ln�m definic�m po��te�n�ho stavu a p�echodov� funkce).

V p��pad�, �e jazyk automatu je pr�zdn�, odevzd�vejte jednostavov� automat nad stejnou abecedou, jako je p�vodn� automat.

Odevzd�vejte zdrojov� soubor, kter� obsahuje implementaci po�adovan� funkce determinize. Do zdrojov�ho souboru p�idejte i dal�� Va�e podp�rn� funkce, kter� jsou z determinize volan�. Funkce bude volan� z testovac�ho prost�ed�, je proto d�le�it� p�esn� dodr�et zadan� rozhran� funkce. Za z�klad pro implementaci pou�ijte k�d z uk�zky n�e. V k�du chyb� vyplnit funkci determinize (a p��padn� dal�� podp�rn� funkce). Uk�zka obsahuje testovac� funkci main, uveden� hodnoty jsou pou�it� p�i z�kladn�m testu. V�imn�te si, �e vkl�d�n� hlavi�kov�ch soubor�, struktur DFA a MISNFA a funkce main jsou zabalen� v bloku podm�n�n�ho p�ekladu (#ifdef/#endif). Pros�m, ponechte bloky podm�n�n�ho p�ekladu i v odevzd�van�m zdrojov�m souboru. Podm�n�n� p�eklad V�m zjednodu�� pr�ci. P�i kompilaci na Va�em po��ta�i m��ete program norm�ln� spou�t�t a testovat. P�i kompilaci na Progtestu funkce main a vkl�d�n� hlavi�kov�ch soubor� "zmiz�", tedy nebude kolidovat s hlavi�kov�mi soubory a funkc� main testovac�ho prost�ed�.

Pro z�klad implementace m��ete vyu��t soubor ke sta�en� n�e v sekci Vzorov� data. Tento soubor obsahuje tak� n�kolik z�kladn�ch test�, m�jte v�ak na pam�ti, �e v�sledky Va�� �mplementace se mohou li�it. Testy jsou nastaveny podle v�sledk�, kter� d�v� jedno z referen�n�ch �e�en�. Mo�n� si je tedy budete muset upravit.

V� program bude spou�t�n v omezen�m testovac�m prost�ed�. Je omezen dobou b�hu (limit je vid�t v logu referen�n�ho �e�en�) a d�le je omezena i velikost dostupn� pam�ti.