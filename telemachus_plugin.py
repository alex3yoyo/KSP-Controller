
# This allows you to more conveniently write scripts that can interface with
# Telemachus
url = 'http://127.0.0.1:8085/telemachus/datalink?alt='
# url = 'http://192.168.1.3:8085/telemachus/datalink?alt='
# This is the URL that Telemachus can be found at.
# Adjust it based on your firewall settings.

import json
import urllib2
import math


class telemachus_plugin():
    def __init__(self):
        print("Init")

    def get_value(self, resource):
        resource_names = {
            "angular_velocity": {"name": "v.angularVelocity", "min": 0, "max": 0},
            "orbital_velocity": {"name": "v.orbitalVelocity", "min": 0, "max": 0},
            "surface_velocity": {"name": "v.surfaceSpeed", "min": 0, "max": 0},
            "vertical_velocity": {"name": "v.verticalSpeed", "min": 0, "max": 0},
            "altitude": {"name": "v.altitude", "min": 0, "max": 0},
            "apoapsis": {"name": "o.ApA", "min": 0, "max": 0},
            "periapsis": {"name": "o.PeA", "min": 0, "max": 0},
            "time_to_apoapsis": {"name": "o.timeToAp", "min": 0, "max": 0},
            "time_to_periapsis": {"name": "o.timeToPe", "min": 0, "max": 0},
            "body": {"name": "v.body", "min": 0, "max": 0},
            "eccentricity": {"name": "o.eccentricity", "min": 0, "max": 0},
            "pitch": {"name": "n.pitch", "min": 0, "max": 0},
            "heading": {"name": "n.heading", "min": 0, "max": 0},
            "roll": {"name": "n.roll", "min": 0, "max": 0},
            "inclination": {"name": "o.inclination", "min": 0, "max": 0},
            "mission_time": {"name": "v.missionTime", "min": 0, "max": 0},
            "orbital_period": {"name": "o.period", "min": 0, "max": 0},
            "throttle": {"name": "f.throttle", "min": 0, "max": 0},
            "universal_time": {"name": "t.universalTime", "min": 0, "max": 0},
            "lights": {"name": "v.lightValue", "min": 0, "max": 0}
        }
        fresh_json = json.load(urllib2.urlopen(
                               url + resource_names[resource["name"]]))
        value = fresh_json["alt"]
        result = {"value": value, "min": , "max"}
        return result

    def read_facing(self, dimension):
        if dimension in ['pitch']:
            fresh_json = json.load(urllib2.urlopen(url + 'n.pitch'))
            result = math.radians(int(fresh_json["alt"]))
        elif dimension in ['yaw']:
            fresh_json = json.load(urllib2.urlopen(url + 'n.heading'))
            result = math.radians(int(fresh_json["alt"]))
        elif dimension in ['roll']:
            fresh_json = json.load(urllib2.urlopen(url + 'n.roll'))
            result = math.radians(int(fresh_json["alt"]))
        else:
            result = -1
        return result

    def read_resource(self, resource):
        reformated_resource = url + 'r.resource' + '[' + resource + ']'
        fresh_json = json.load(urllib2.urlopen(reformated_resource))
        result = fresh_json["alt"]
        return result

    def read_resource_max(self, resource):
        reformated_resource = url + 'r.resourceMax' + '[' + resource + ']'
        fresh_json = json.load(urllib2.urlopen(reformated_resource))
        result = fresh_json["alt"]
        return result

    # Output Definitions
    def abort(self):
        urllib2.urlopen(url + 'f.abort')

    def fly_by_wire(self, var):
        urllib2.urlopen(url + 'v.setFbW' + '[' + str(var) + ']')

    def brake(self, var):
        if var == 2:
            #fresh_json = json.load(urllib2.urlopen(url + 'v.gearValue'))
            #return fresh_json["alt"]
            return (-1)
            print 'The brake:read feature is not yet support by telemachus'
        elif var == 1:
            urllib2.urlopen(url + 'f.brake' + '[' + 'true' + ']')
            print 'Setting Brake to on'
        elif var == 0:
            urllib2.urlopen(url + 'f.brake' + '[' + 'false' + ']')
            print 'Setting Brake to off'
        else:
            return (-1)
            print 'Brake value was set wrong'

    def gear(self, var):
        if var == 2:
            #fresh_json = json.load(urllib2.urlopen(url + 'v.gearValue'))
            #return fresh_json["alt"]
            return (-1)
            print 'The gear:read feature is not yet support by telemachus'
        elif var == 1:
            urllib2.urlopen(url + 'f.gear' + '[' + 'true' + ']')
            print 'Setting Gear to on'
        elif var == 0:
            urllib2.urlopen(url + 'f.gear' + '[' + 'false' + ']')
            print 'Setting Gear to off'
        else:
            return (-1)
            print 'Gear value was set wrong'

    def light(self, var):
        if var == 2:
            fresh_json = json.load(urllib2.urlopen(url + 'v.lightValue'))
            if fresh_json["alt"] == "True":
                return 1
            elif fresh_json["alt"] == "False":
                return 0
            else:
                return fresh_json["alt"]
        elif var == 1:
            urllib2.urlopen(url + 'f.light' + '[' + 'true' + ']')
            print 'Setting Light to TRUE'
        elif var == 0:
            urllib2.urlopen(url + 'f.light' + '[' + 'false' + ']')
            print 'Setting Light to False'
        else:
            return (-1)
            print 'Light value was set wrong'

    def rcs(self, var):
        if var == 2:
            fresh_json = json.load(urllib2.urlopen(url + 'v.rcsValue'))
            if fresh_json["alt"] == "True":
                return 1
            elif fresh_json["alt"] == "False":
                return 0
            else:
                return fresh_json["alt"]
        elif var == 1:
            urllib2.urlopen(url + 'f.rcs' + '[' + 'true' + ']')
            print 'Setting RCS to TRUE'
        elif var == 0:
            urllib2.urlopen(url + 'f.rcs' + '[' + 'false' + ']')
            print 'Setting RCS to False'
        else:
            return (-1)
            print 'RCS value was set wrong'

    def sas(self, var):
        if var == 2:
            fresh_json = json.load(urllib2.urlopen(url + 'v.sasValue'))
            if fresh_json["alt"] == "True":
                return 1
            elif fresh_json["alt"] == "False":
                return 0
            else:
                return fresh_json["alt"]
        elif var == 1:
            urllib2.urlopen(url + 'f.sas' + '[' + 'true' + ']')
            print 'Setting SAS to TRUE'
        elif var == 0:
            urllib2.urlopen(url + 'f.sas' + '[' + 'false' + ']')
            print 'Setting SAS to False'
        else:
            return (-1)
            print 'SAS value was set wrong'

    def stage(self):
        urllib2.urlopen(url + 'f.stage')

    def set_facing(self, dimension, angle):
        # Done by setting relative positions from 0 to 1, as a percent
        # Based on the three bars in the lower left corner, NOT the Navball
        if dimension in ['pitch']:
            urllib2.urlopen(url + 'v.setPitch' + '[' + str(angle) + ']')

        elif dimension in ['yaw']:
            urllib2.urlopen(url + 'v.setYaw' + '[' + str(angle) + ']')

        elif dimension in ['roll']:
            urllib2.urlopen(url + 'v.setRoll' + '[' + str(angle) + ']')

    def set_throttle(self, throttle):
        urllib2.urlopen(url + 'f.setThrottle' + '[' + str(throttle) + ']')

    def toggle_ag(self, agn):
        urllib2.urlopen(url + 'f.ag' + agn)
