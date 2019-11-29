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
#import io
import json
import time
import logging

class Pipes:
    """
    C'est une classe abstraite qui met en oeuvre un tube nommé en lecture (seule).
    Elle permet l'instanciation avec "with" et la lecture de messages arrivant sous la forme d'un objet.
    Elle utilise une sérialisation JSON pour assurer l'échange des objets.
    """

#    _pathControler = "/tmp/controler"

    def __init__(self, path):
        self._mainPath = path
        
    def __enter__(self):
        try:
            os.mkfifo(self._mainPath)
            logging.debug("Tube créé ({})".format(self._mainPath))
        except FileExistsError:
            logging.warning("Tube déjà existant ({}).".format(self._mainPath))
        finally:
            self._fifo = os.open(self._mainPath, os.O_RDONLY | os.O_NONBLOCK)
            
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        os.close(self._fifo)
        os.remove(self._mainPath)
        logging.debug("Tube supprimé ({}).".format(self._mainPath))
        
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

    def writeMessage(self, path, mes):
        for i in range(0, 6): 
            try:
                ctrl = os.open(path, os.O_WRONLY | os.O_NONBLOCK)
                os.write(ctrl, bytearray(json.dumps(mes), 'utf-8'))
                os.close(ctrl)
                return
            except FileNotFoundError:
                logging.debug("Attention ! Tube nommé {} introuvable, réessai dans 10 sec {}".format(path, i))
                time.sleep(10);
                continue                
        

            
class PipesControl(Pipes):
    """
    C'est la classe concrête destinée au Contrôleur.
    Elle instancie un tube nommé sur lequel le contrôleur lit les messages transmis par les modules.
    Elle permet de transmettre des messages à chacun des modules.
    Chaque module doit s'identifié lors de son démarrage pour être reconnu par contrôleur.
    """
    
    def __init__(self):
        super().__init__("/tmp/control")


class PipesModule(Pipes):
    """
    C'est la classe concrête destinée aux différents modules.
    Elle instancie un tube nommé sur lequel le module lit les messages transmis par le contrôleur.
    Elle permet de transmettre des messages au contrôleur.
    Le module s'identifie lors de son démarrage pour être reconnu par contrôleur.
    """

    def __init__(self, name):
        self._moduleName = name
        super().__init__("/tmp/{}".format(name))
        
    def record(self):
        logging.debug("Enregistrement de {} auprès de /tmp/control".format(self._moduleName));
        self.writeMessage('/tmp/control', { 'verbe': 'hello', 'source': self._moduleName, 'path': self._mainPath } )

if __name__ == "__main__":
    raise RuntimeError("Ne pas exécuter cette classe !")