
---------------  Εκτέλεση Προγράμματος -------------------------

 ́Εχει δημιουργηθεί MakeFile,γίνεται compile των αρχείων με την εντολή “make” και
στην συνέχεια το πρόγραμμα εκτελείτε με τον εξής τρόπο:

./pi τιμή πλευράς τιμή πλευράς ..... τιμή πλευράς τιμή δοκιμών
(πχ ./pi 2 54 6 78 34 1000000)

Έχει γίνει η παραδοχή ότι οι τιμές πλευρών και δοκιμών που θα λάβει ως παραμέτρους
το πρόγραμμα είναι τύπου int. Δεν υπάρχει έλεγχος σε περίπτωση εισαγωγής μη
αποδεκτής τιμής.


------------------------- Περιγραφή υλοποίησης -------------------------------

1.Αρχικά δεσμεύεται μνήμη για 2 πίνακες.
α) πίνακας sides_array (Τύπου Sides) - κρατούνται όλες οι πληροφορίες για τον
υπολογισμό των στατιστικών.
-Τιμή πλευράς(side)
-Πλήθος δοκιμων για την πλευρά αυτή (tests)
-Πλήθος δοκιμών όπου τοσημείο βρέθηκε εντός του κύκλου.
β) πίνακας proc_ids(τύπου pid_t) -εκεί αποθηκεύονται τα ids όλων των διεργασιών που
δημιουργούνται.

2.Αρχικοποίηση των πινάκων.

3. Δημιουργία της shared memory (Τύπου Memory).
Στην sm αποθηκεύεται:
-Η τιμή της πλεράς για την οποία θα γίνει η δοκιμή (x)
-Αν το σημείο βρέθηκε μέσα στον κύκλο(1) ή όχι (0) (in_out)
-Αν η προσομοίωση έχει ολοκληρωθεί ή όχι (quit)

4.Δημιουργία n+1 σημαφόρων, όπου n το πλήθος των διεργασιών που θα
δημιουργήσουμε και ένας σημαφόρος για την parent process. Αρχικοποίηση αυτών σε 0.

5. Δημιουργία n διεργασιών όπου επιχειρούν να κάνουν down στο σημαφόρο που τους
έχει εκχωρηθεί και μπλοκάρονται.

6. Εκτέλεση parent process η οποία για πλήθος δοκιμών ,
α)παράγει ένα τυχαίο k (εύρος k είναι από 0 εως πλήθος πλευρών -1)
β)γράφει στην μνήμη την τιμή της πλευρά που παράγεται
γ)κάνει up τον σημαφόρο της k διεργασίας και down τον δικό της σημαφόρο ώστε να
μπλοκαριστεί και να μην εκτελεστεί μέχρι να έχει “απάντηση” από την child process που
έχει αφυπνιστεί.
Η εν λόγω διεργασία αρχίζει να εκτελείτε δηλ διαβάζει από την μνήμη την τιμή της
πλευράς, υπολογίζει με την συνάρτηση square() αν το τυχαίο σημείο βρίσκεται μέσα
στον κύκλο ή όχι και ενημερώνει κατάλληλα την shared memory.Κάνει up τον σημαφόρο της parent process και down τον δικό της ώστε να
μπλοκαριστεί ξανά.
δ)Η parent process “διαβάζει” αυτά που έχει “γράψει” η child process και ενημερώνει
τον πίνακα sides_array.

7.Μετά την ολοκλήρωση των δοκιμών , η parent process αλλάζει την τιμή της κοινής
μεταβλητής quit και “ξυπνά” μια μια τις child processes ώστε να εκτελεστούν και να
κάνουν exit.

8.Εκτύπωση του πίνακα proc_ids (δεν ζητείται).

9. Εκτύπωση των στατιστικών.

10. dettach και καταστροφή της shared memory, καταστροφή των
σημαφόρων,αποδέσμευση του χώρου που είχε δεσμευτεί για τους 2
πίνακες.Ολοκλήρωση Εκτέλεσης.


--------------- Αρχεία ------------------------------------------

main.c
Δημιουργία πινάκων, κοινής μνήμης, σημαφόρων,εκτέλεση διεργασίων.

Square.c/Square.h
Συνάρτηση παραγωγής ενός τυχαίου σημείου (x.y) και υπολογισμός αν βρίσκεται μέσα
στον κύκλο ή όχι.(square()).
Συναρτήσεις αρχικοποίησης πινάκων.(init_sides_array() &init_proc_ids())
Συναρτήσεις εκτύπωσης δεδομένων.(print_data() & print_proc_ids())


SharedMemory.c/SharedMemory.h
Συναρτήσεις δημιουργίας και καταστροφής της shared memory.
Συναρτήσεις εγγραφής δεδομένων (write_data()) και ανάγνωσης
δεδομένων(read_data()) από την shared memory.

Semaphores.c/Semaphores.h
Συναρτήσεις δημιουργίας, καταστροφής set σημαφόρων και πράξεων up, down.
