#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import io
import json

class Pipes:
    """
    Définit et met en oeuvre la communication au travers de tubes nommés.
    Peut s'utiliser avec "with".
    """

    def __init__(self, path):
        self._mainPath = path
        
    def __enter__(self):
        self._createPipe(self._mainPath)
        self._fifo = os.open(self._mainPath, os.O_RDONLY | os.O_NONBLOCK)
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        os.close(self._fifo)
        self._deletePipe(self._mainPath)
        
    def getMainPath(self):
        return self._mainPath

    def _createPipe(self, path):
        try:
            os.mkfifo(path)
            print("Tube créé ({})".format(path))
        except FileExistsError:
            print("Tube déjà existant ({}).".format(path))

    def _deletePipe(self, path):
        os.remove(path)
        print("Tube supprimé ({}).".format(path))
        
    def readMessage(self):
        s = bytearray()
        while True:
            try:
                s.append(os.read(self._fifo, 1)[0])
                dec = json.loads(s)
                return dec

            except IndexError:                 # os.read empty
                return None
            
            except BlockingIOError as err:
                if err.errno == 11:           # Resource temporarily unavailable
                    return None
            
            except json.JSONDecodeError:       # json invalide
                pass
            
if __name__ == "__main__":
    modules = list()
    with Pipes("/tmp/controle") as pipes:
        while True:
            r = pipes.readMessage()
            if r:
                try:
                    e = r['hello']
                    modules.append(e);
                except KeyError:
                    print("Message ignoré (", end='')
                    print(r, end='')
                    print(") !")
                    print("'{ \"hello\": nom de pipe de l'émetteur }' attendu !")
                    continue
                
                print(e)
                
#            else:
#                break
