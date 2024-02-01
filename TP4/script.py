
from owlready2 import *

onto = get_ontology("http://testxyz.org/onto.owl") #create ontology using iri

with onto: #defining our ontology

    ##Defining concepts##
    class Personne (Thing) :
        pass

    class Aliment (Thing):
        pass

    class University (Thing):
        pass

    AllDisjoint ([Personne, Aliment, University]) #pour dire qu'un invidivu ne peut pas etre une personne et un aliment

    ##Defining roles##
    class mange (Personne >> Thing):
        pass

    class enseigne(Personne >> Thing): #persone est thing
        pass

    class enseigne_par(ObjectProperty):
        inverse_property = enseigne

    class mange_par(ObjectProperty):
        inverse_property = mange

    class PartieDe(Thing >> Thing):
        pass

    ##Defining composed entities##
    class Faculty (Thing):
        equivalent_to = [Thing & PartieDe. some (University) ]

    class Departement (Thing):
        equivalent_to = [Thing & PartieDe. some (Faculty) ]

    class Enseignant (Personne) :
        equivalent_to = [Personne & enseigne. only (Personne) ]

    class Etudiant (Thing):
        equivalent_to = [Personne & enseigne_par.only (Enseignant)]

    ##defining instances ABOX##

    class Hamza (Thing):
        equivalent_to = [Personne & mange. only (Aliment ) ]

    class Khellaf (Personne):
        equivalent_to = [Enseignant & mange. some (Aliment) & enseigne. only (Etudiant ) ]

    class MalBouffe (Thing) :
        equivalent_to = [Aliment & (mange_par.some(Personne) ) ]

    AllDisjoint ([Etudiant, Enseignant])
    AllDisjoint ([Khellaf, Hamza])
    AllDisjoint ([MalBouffe, Departement, Faculty, University])

    sync_reasoner_pellet (infer_property_values=True)
    onto.save (file = "tp_rc1.owl", format = "rdfxml")

with onto:

    USTHB = onto. University ()
    thameur = onto. Etudiant ()
    Chocolat = onto. Aliment ()
    belhadi = onto. Personne ()

    SI = Thing () #department
    INFO = Thing() #faculty

    INFO.PartieDe.append(USTHB)
    SI.PartieDe.append(INFO)

    thameur.mange = [Chocolat]
    belhadi.enseigne = [thameur]

    sync_reasoner_pellet (infer_property_values=True)
    onto.save(file = "tp_rc2.owl", format = "rdfxml")



# Printing inferred results
# print("Inferred individuals:")
# for individual in onto.individuals():
#     print(individual)

# print("\nInferred types:")
# for individual in onto.individuals():
#     print(f"{individual} has types: {individual.is_a}")

# print("\nInferred properties:")
# for individual in onto.individuals():
#     print(f"{individual} has properties:")
#     for prop in individual.get_properties():
#         print(f"  {prop} : {individual.get_properties(prop)}")