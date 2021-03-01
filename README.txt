Έφτιαξα τα spells items heroes
Αυριο θα υλοποιησω το use του Potion, (ισως φτιαξω dexPotion, agilPotion, strPotion, για
 να buffαρω συγκεκριμενο stat του καθε ηρωα)



Οι buy/exit καλούνται αρχικά από το tile το οποίο ελέγχει αν ειναι
τύπου Market και αν υπάρχει σε αυτό κάποιος Hero.
Τότε, η buy εκτελείται απο το ίδιο το tile, ενώ η sell καλεί
την αντίστοιχη sell του Hero, για να γίνεται πιο εύκολα πρόσβαση στο 
inventory του.