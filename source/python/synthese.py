#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pipes import PipesModule
import logging
logging.basicConfig(level=logging.DEBUG)
#logging.basicConfig(level=logging.WARNING)
from espeakng import ESpeakNG

    
def direTout():
    esng = ESpeakNG(voice='fr')

    esng.say('Bonjour.', sync=True)
    s = 'Bienvenue a la mediatheque '
    esng.say(s + '.', sync=True)
   

    
def finir(obj):
    logging.debug("Arrêt commandé du Module synthese.")
    exit(0)
    
def parler(obj):
    logging.debug("Commande PARLER.")

def init(obj):
    logging.debug("Commande d'initialisation du module.")
    esng = ESpeakNG(voice='fr')

    s = 'Bienvenue à la mediatheque '
    esng.say(s, sync=True)
    
if __name__ == "__main__":
    logging.debug("Démarrage du module synthese.")
    esng = ESpeakNG()
#print(esng.voices) 
    
    with PipesModule("synthese") as pipes:
        pipes.record()
        while True:
            obj = pipes.readMessage()
            if obj:
                logging.debug("Message reçu : {}".format(obj))
                try:
                    switcher = {
                        'fin': finir,
                        'init': init,
                        'parler': parler
                    }[obj['verbe']](obj)
                except KeyError:
                    logging.warning("Commande inattendue, message ignoré ({}) !".format(obj))
                    continue
                