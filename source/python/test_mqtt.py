#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright 2019 Marc SIBERT
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import pickle
import time
import paho.mqtt.client as mqtt

import logging
logging.basicConfig(level=logging.DEBUG)
#logging.basicConfig(level=logging.WARNING)


def on_message(mqttc, obj, msg):
    print(pickle.loads(msg.payload))
    print(msg.mid)
#    print(msg.topic + " " + str(msg.qos) + " " + pickle.loads(msg.payload))

def main():
    host = "localhost"
    port = 1883
    
    client = mqtt.Client(client_id="controler", clean_session=True)

    try:
        client.will_set("/robot-roulant/controler/will", "Mort brutale !")
        client.connect(host, port)
        client.loop_start()
        client.on_message = on_message

    except ConnectionRefusedError as e:
        logging.error("Connexion refusée ! ({})".format(e))
        raise

    client.subscribe("/robot-roulant/synthese", qos=2)

    for i in range(100):
        mes = {
            'source': 'controler',
            'verbe': 'hello',
            'param': hash( "controler-{}".format(i) )
        }
        
        info = client.publish("/robot-roulant/synthese", pickle.dumps(mes), qos=2)
        if info.rc != 0:
            logging.warning("Attention : {} !".format( mqtt.error_string(info.rc) ))

        print("Message {} enregistré.".format(info.mid) )
    

    time.sleep(20)



    client.loop_stop()
    client.disconnect()




if __name__ == "__main__":
    main()    
