#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright 2019 Marc SIBERT
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#import os
#import io
#import json
#import time
import logging

class MQTTAbstract:
    """
    C'est une classe abstraite qui met en oeuvre un topic.
    Elle permet l'instanciation avec "with" et la lecture de messages arrivant sous la forme d'un objet.
    Elle utilise une sérialisation "pickle" pour assurer l'échange des objets.
    """

    _mainPath = "/robot-roulant"
    _pathControler = _mainPath + "/controler"
    _MQTTHost = "localhost"
    _MQTTPort = 1883
    
    def __init__(self, path, id):
        self._path = path
        self._client = mqtt.Client(client_id=id, clean_session=True)

class MQTTControl(MQTTAbstract):
    """
    C'est la classe concrête destinée au Contrôleur.
    Elle instancie un topic sur lequel le contrôleur lit les messages transmis par les modules.
    Elle permet de transmettre des messages à chacun des modules.
    Chaque module doit s'identifier lors de son démarrage pour être reconnu par contrôleur.
    """
    
    def __init__(self):
        super().__init__(_pathControler, "controler")
        
    def __enter__(self):
        try:
            logging.debug("Connection du contrôleur.")
            client.connect(_MQTTHost, _MQTTPort)
            client.loop_start()
#            client.on_message = on_message
            client.subscribe(_pathControler, qos=2)
        except ConnectionRefusedError as e:
            logging.error("Connexion refusée ! ({})".format(e))
            raise
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        client.loop_stop()
        client.disconnect()    
    