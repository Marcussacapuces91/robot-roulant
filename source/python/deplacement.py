#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pipes import PipesModule

def finir():
    print("Arrêt commandé du Module deplacement.")
    exit(0)
    
def avancer(dist = 1):
    pass
            
if __name__ == "__main__":
    print("Démarrage du module deplacement.")
    with PipesModule("deplacement") as pipes:
        pipes.record()
        while True:
            obj = pipes.readMessage()
            if obj:
                print("Message reçu : {}".format(obj))
                switcher = {
                    'fin': finir,
                    'avancer': avancer
                }[obj['verbe']]()
    