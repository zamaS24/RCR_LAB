from owlready2 import get_ontology

# Load the ontology from the saved file
onto = get_ontology("tp_rc2.owl").load()

# Print inferred individuals
print("Inferred individuals:")
for individual in onto.individuals():
    print(individual)

# Print inferred types
print("\nInferred types:")
for individual in onto.individuals():
    print(f"{individual} has types: {individual.is_a}")

# Print inferred properties
print("\nInferred properties:")
for individual in onto.individuals():
    print(f"{individual} has properties:")
    for prop in individual.get_properties():
        prop_values = getattr(individual, prop.name)  # Use prop.name to get the property name as a string
        print(f"  {prop} : {prop_values}")
