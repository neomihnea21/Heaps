import random

# 1 - inserare   2 - afisare si stergere maxim  3 - reuniune

def generate_input(filename):
        # daca crapa, micsoram N sau Q
        N = random.randint(1,100)
        Q = random.randint(1,300000)
        with open(filename, 'w') as f:
            f.write(f"{N} {Q}\n")
            for _ in range(Q):
                op_type = random.choice([1,2,3], weights = [0.6, 0.2, 0.2])  # ajustare ponderi pentru testare cazuri limita a heapului - acum fortam nr de inserari
                # idee, 0.4 pentru inserari, 0.4 pentru reuniune si 0.2 pentru afisare etc
                if op_type == 2:
                    # e nevoie doar de o multime
                    my_set = random.randint(1, N)
                    f.write(f"{op_type} ")
                    f.write(f"{my_set}\n")
                else:
                    if op_type == 1:
                        # e nevoie de o multime si un nr
                        my_set = random.randint(1, N)
                        x = random.randint(1, 2000000000)
                        f.write(f"{op_type} {my_set} {x}\n")
                    else:
                        # e nevoie de 2 multimi
                        my_set1 = random.randint(1,N)
                        my_set2 = random.randint(1,N)
                        f.write(f"{op_type} {my_set1} {my_set2}\n")


