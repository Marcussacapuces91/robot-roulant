#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
  Copyright 2019 Marc SIBERT

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
"""

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
            
    def writeMessage(self,mes):
        os.write(self._fifo,json.dumps(mes)) # on a transformé  l'objet "mes"  en chaine de caracteres au format json
