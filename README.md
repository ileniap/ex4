#Esercizio 4 NOTE

Si è sviluppato un action lib in cui si sono impostati come goal:
-qi = posizione iniziale
-qd = posizione finale desiderata
-wmax = velocità massima 
-dtime = tempo di esecuzione desiderato

Il server viene inizializzato e nella executeCB viene effettuata tutta la computazione necessaria al raggiungimento dell'obiettivo finale. In particolare si è calcolata l'accelerazione uniforme con la formula:

	a=(goal->qd-goal->qi)/((goal->dtime)*(goal->dtime))

Settando valori di current_speed (curr_speed), current_position si è passato al calcolo della posizione corrente attraverso la formula

 current_position = goal->qi +0.5*a*(current_time*current_time)

E si è immagazzinata nella variabile progress per tener traccia del feedback, per poi pubblicarlo.

Vengono fatti opportuni controlli sulla velocità corrente (con un if), sul tempo (current_time) etc.

Client

Nel client si è deciso inizialmente di optare per un inserimento user-friendly da tastiera attraverso il comando cin e poi si assegnato tale valore ai campi dei goal.
In alternativa c'è la possibilità di utilzizare la funzione "atoi(argv[...]) per gli inserimenti. L'input però viene fornito al momento del run del client nel seguente modo:

	rosrun ros_motor motor_client 1 10 100 50

dove 1 10 100 50 sono gli argc in riferimento rispettivamente ai goal sopracitati.
Nel caso si volesse percorrere questa alternativa è utile (o necessario) ricorrere preventivamente (all'inizio del codice) attraverso un if ad un controllo degli argc. 


E' possibile introdurre anche altri controlli per migliorare il codice, quali generazioni di messaggi di errore o altro.

Ilenia Perrella



