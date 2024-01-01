"""
Upload events.
"""

from __future__ import print_function
import os, argparse, sys, uuid, datetime, boto3, re, glob, gzip, json
from boto3.dynamodb.conditions import Key
from decimal import *
import time
import random

parser = argparse.ArgumentParser()
parser.add_argument("--path", help="Path that contains items to start to upload", default='./examples')
parser.add_argument("--t", help="Date to. YYYY-mm-dd date to finish the script", default='2030-01-20')
parser.add_argument("--f", help="Date from. YYYY-mm-dd date to finish the script", default='2007-01-01')
parser.add_argument("--bucket_name", help="Bucket name with stored events", default=None)

pattern = re.compile(".*_\d{8}([A-Z])\w+.json.gz")

filterEventNames = ["assume","get", "describe", "list", "info", "decrypt", "checkmfa", "head"]
index = 'userIdentity_userName-eventTime-index'



# ====== UseDynamoDB =========
class UseDynamoDB:
    """Class used to store items on DynamoDB"""
    
    def __init__(self, name, verbose=False):
        self.name = name
        self.index = index
        self.verbose = verbose

    
    def store_event(self, name_table, event):

        dynamodb = boto3.resource('dynamodb')
        table = dynamodb.Table(name_table)
        nameCamp = 'userIdentity_userName'

        for datos in event.events():
            """Every event file has one or more events"""
            if self.verbose:
                print('Event request: {0}'.format(datos))

            name_event = datos.get("eventName", None)
            if name_event is None or name_event.lower().startswith(tuple(filterEventNames)):
                # print("Evento no")
                continue

            userName = datos.get(nameCamp, None)
            if userName is None:
                datos[nameCamp] = 'no_user'

            table.put_item(
                Item=datos
            )

            if self.verbose:
                print("PutItem succeeded:")

            ## Adding new user
            if userName is None or userName == ' ':
                userName = 'no_user'

            ## Adding a new service
            service_name = datos.get("eventSource", None)
            if service_name:
                service_name = service_name.split(".")[0]

            ## Ading columns
            columns = datos.keys()

            ## Adding all
            self.news(name_table, userName, service_name, columns)

    def news(self, name_table, user, service, new_columns):
        """Get an user and add it if not exist yet"""
        index = 'userIdentity_userName'
        setValue_cols = 'cols'
        setValue_services  = 'services'
        setValue_listUsers = 'listUsers'
        arr = ['userIdentity_userName', 'all']
        # eventos = resource.Table(name_table)
        dynamodb = boto3.resource('dynamodb')
        table = dynamodb.Table(name_table)

        # filter expression
        fe = Key(arr[0]).eq(arr[1]);
        response = table.query(
            IndexName=self.index,
            KeyConditionExpression=fe,
        )
        cols = response['Items'][0][setValue_cols]
        services = response['Items'][0][setValue_services]
        users = response['Items'][0][setValue_listUsers]
        # users = ast.literal_eval(users)
        aux = False
        for column in new_columns:
            if cols.get(column, None) is None:
                aux = True
                cols[column] = '1'

        if users.get(user,None) is None:
            aux = True
            users[user] = '1'

        if services.get(service, None) is None:
            aux = True
            services[service] = '1'

        if not aux: return
        # update
        table.update_item(
            Key={
                'eventID': '1',
                'userIdentity_userName': 'all',
            },
            UpdateExpression=("SET {0} = :p, {1} = :r, {2} = :q").format(setValue_cols, setValue_services, setValue_listUsers),
            ExpressionAttributeValues={
                ':p': cols,
                ':r': services,
                ':q': users,
            },
            ReturnValues="UPDATED_NEW"
        )

# ====================

# ====== Event =====
"""Clase para un solo archivo de eventos"""
class Event:
    
    CLOUDTRAIL_EVENT_DATETIME_FORMAT = '%Y-%m-%dT%H:%M:%SZ'
    
    def __init__(self, archive_base_dir):
        # store base dir to CloudTrail archives
        self.file = archive_base_dir.rstrip('/')
        fp = gzip.open(self.file, 'rt')
        self.all_events = json.loads(fp.read())
        fp.close()
        """Values that we want to store of an event"""
        self.selected = [
            "eventID",
            "userIdentity_userName",
            "awsRegion",
            "eventName",
            "eventSource",
            "eventTime",
            "eventType",
            "userAgent",
            "userIdentity_principalId",
            "requestParameters_bucketName",
            "requestParameters_dBInstanceIdentifier",
            "requestParameters_dBSecurityGroupName",
            "requestParameters_includeAllInstances",
            "requestParameters_includeDeleted",
            "requestParameters_instanceType",
            "requestParameters_roleSessionName",
            "requestParameters_volumeSet_items_0_volumeId",
            "responseElements_credentials_accessKeyId",
            "responseElements_credentials_expiration",
            "responseElements_credentials_sessionToken",

            # "userIdentity_type",
            # "userIdentity_accountId",
            # "userIdentity_arn",
            # "responseElements",
            # "userIdentity_accessKeyId",
            # "userIdentity_sessionContext_attributes_creationDate",
            # "userIdentity_sessionContext_attributes_mfaAuthenticated",
            # "userIdentity_invokedBy",
            # "resources_0_ARN",
            # "resources_0_accountId",
            # "resources_0_type",
            # "readOnly",
            # "requestParameters_encryptionContext_aws:lambda:FunctionArn",
            # "requestParameters_instancesSet_items_0_instanceId",
            # "requestParameters_filterSet_items_0_name",
            # "requestParameters_filterSet_items_0_valueSet_items_0_value",
            # "userIdentity_sessionContext_sessionIssuer_accountId",
            # "userIdentity_sessionContext_sessionIssuer_arn",
            # "userIdentity_sessionContext_sessionIssuer_principalId",
            # "userIdentity_sessionContext_sessionIssuer_type",
            # "userIdentity_sessionContext_sessionIssuer_userName",
            # "requestParameters",
            # "errorCode",
            # "errorMessage",
            # "requestParameters_maxRecords",
            # "requestParameters_accountAttributeNameSet_items_0_attributeName",
            # "requestParameters_availabilityZone",
            # "requestParameters_blockDeviceMapping_items_0_deviceName",
            # "requestParameters_blockDeviceMapping_items_0_ebs_deleteOnTermination",
            # "requestParameters_blockDeviceMapping_items_0_ebs_volumeSize",
            # "requestParameters_blockDeviceMapping_items_0_ebs_volumeType",
            # "requestParameters_clientToken",
            # "requestParameters_clusterId",
            # "requestParameters_disableApiTermination",
            # "requestParameters_environmentId",
            # "requestParameters_environmentIds_0",
            # "requestParameters_externalId",
            # "requestParameters_force",
            # "requestParameters_groupSet_items_0_groupId",
            # "requestParameters_instancesSet_items_0_imageId",
            # "requestParameters_instancesSet_items_0_keyName",
            # "requestParameters_instancesSet_items_0_maxCount",
            # "requestParameters_instancesSet_items_0_minCount",
            # "requestParameters_location_0",
            # "requestParameters_maxResults",
            # "requestParameters_monitoring_enabled",
            # "requestParameters_roleArn",
            # "responseElements_instancesSet_items_0_currentState_code",
            # "responseElements_instancesSet_items_0_currentState_name",
            # "responseElements_instancesSet_items_0_instanceId",
            # "responseElements_instancesSet_items_0_previousState_code",
            # "responseElements_instancesSet_items_0_previousState_name",
            # "sharedEventID",
            # "eventVersion",
            # "recipientAccountId",
            # "requestID",
            # "sourceIPAddress",
            # "responseElements_assumedRoleUser_arn",
            # "responseElements_assumedRoleUser_assumedRoleId",
            # "requestParameters_snapshotId",
            # "requestParameters_stackName",
        ]

    def count_events(self):
        return len(self.all_events['Records'])
    
    def events(self):

    
        if ('Records' in self.all_events):
        
            for trail_item in self.all_events['Records']:
                yield self.build_event(trail_item)

    """Function for select only the values that we are searching - 
    Filter """
    def select(self, flat={}):
        res = {}
        for k in self.selected:
            r = flat.get(k, None)
            if r:
                res[k] = r
        return res

    def build_event(self, source):
        # print("\n\n %s source" % source)
        flat = flatten_json(source)
        # f = json_normalize(flat)
        # print("\n %s flatten" % f)
        flat = self.select(flat)
        # print(flat)
        # exit()
        return flat

    """Pasa los datos largos (listas, dicts, elementos simples..)
    a un solo objeto del mismo tipo"""

    def strip_data(self, data):
        data_type = type(data)
    
        # recursively process via strip_data() both list and dictionary structures
        if (data_type is list):
            return [
                self.strip_data(list_item)
                for list_item in data
            ]
    
        if (data_type is dict):
            return {
                self.strip_data(dict_key): self.strip_data(dict_value)
                for (dict_key, dict_value) in data.items()
            }
    
        if (data_type is str):
            # if unicode cast to string
            data = str(data)
    
        return data
#===============

def flatten_json(y):
        out = {}

        def flatten(x, name=''):
            if type(x) is dict:
                for a in x:
                    flatten(x[a], name + a + '_')
            elif type(x) is list:
                i = 0
                for a in x:
                    flatten(a, name + str(i) + '_')
                    i += 1
            else:
                if (x == "" or x == None):
                    x = " "
                #verifi if is a number and a decimal to pass as Decimal('')
                elif(isinstance(x,float)):
                    x = Decimal(str(x))

                out[name[:-1]] = x

        flatten(y)
        return out

def order_by_event(list_events):
    """
    Aux method for order a list of events.
    Remove not valid events

    :param list_events: list of strings [path/974349055189_CloudTrail_us-east-1_20170602T1040Z_i2yVtZoWqtLlq5oA.json.gz']
    :return: ordered list of tuple (date, string)
    """
    #split into string dates, covert to datetime
    dates = []
    events = []
    # dates = [datetime.datetime.strptime(e.split("_")[-2][:8], "%Y%m%d") for e in list_events]
    for e in list_events:
        try:
            dates.append(datetime.datetime.strptime(e.split("_")[-2][:8], "%Y%m%d"))
            events.append(e)
        except :
            """
            Not valid date
            """
            continue
    dates = list(zip(dates, events))
    dates.sort()
    return dates

def get_structure(path):
    res = []
    for (path,i,j) in os.walk(path):
        # print(path)
        # print(j)
        if len(j) > 0:
            aux = [os.path.join(path,x) for x in j]
            res.extend(aux)
    return res


def upload_events(path, table_name, to, from_):
    """Get all events from path, upload them and do a tracing.
    All tracing stored items is saved at path_tracing file.
    You can recall this functions without delete this file and start where you left"""
    to_finish = datetime.datetime.strptime(to, "%Y-%m-%d")
    from_start = datetime.datetime.strptime(from_, "%Y-%m-%d")
    path_tracing  = "tracing_items"
    print("Path of files: %s with " % (path))

    if not os.path.exists(os.path.join(path_tracing)):
        f = open(path_tracing, "w")
        f.close()

    file_trace = open(path_tracing, "r")

    traced_items = file_trace.readlines()
    traced_items = [x[:-1] for x in traced_items]
    file_trace.close()
    print("Traced files: %d" % (len(traced_items)))
    events = get_structure(path)
    print("Number of files: %d" % len(events))
    events = list(set(events) - set(traced_items))
    print("Number of total files to upload: %d" % len(events))

    events = order_by_event(events)

    #debug
    start_time = time.time()
    all_time = []
    #fin debug
    file_trace = open(path_tracing, "a+")
    for (e_date, e) in events:  # e = events file
        # debug
        start_event = time.time()
        if from_start > e_date:
            continue;
        if to_finish < e_date:
            break
        event = Event(e)

        db = UseDynamoDB("Uploading", verbose=False)
        print("Uploading " + event + " to " + table_name)
        db.store_event(table_name, event)
        file_trace.write(e+"\n")
        file_trace.flush()

        # debug
        elapsed_event = time.time() - start_time
        all_time.append(elapsed_event)
    # debug
    elapsed_time = time.time() - start_time
    print("Total time: %f" % elapsed_time)
    mean = sum(all_time) / len(all_time)
    print("mean time per event: %f" % mean)
    file_trace.close()
    os.remove(path_tracing)


def get_matching_s3_keys(bucket, prefix='', suffix=''):
    """
    Generate the keys in an S3 bucket.

    :param bucket: Name of the S3 bucket.
    :param prefix: Only fetch keys that start with this prefix (optional).
    :param suffix: Only fetch keys that end with this suffix (optional).
    """
    s3 = boto3.client('s3')
    kwargs = {'Bucket': bucket}

    # If the prefix is a single string (not a tuple of strings), we can
    # do the filtering directly in the S3 API.
    if isinstance(prefix, str):
        kwargs['Prefix'] = prefix
    res = []
    while True:

        # The S3 API response is a large blob of metadata.
        # 'Contents' contains information about the listed objects.
        resp = s3.list_objects_v2(**kwargs)
        for obj in resp['Contents']:
            key = obj['Key']
            if key.startswith(prefix) and key.endswith(suffix):
                res.append( key)

        # The S3 API is paginated, returning up to 1000 keys at a time.
        # Pass the continuation token into the next response, until we
        # reach the final page (when this field is missing).
        try:
            kwargs['ContinuationToken'] = resp['NextContinuationToken']
        except KeyError:
            break
    return res

def upload_events_from_bucket( bucket, to,from_, table_name, download_path="tmp-" + str(random.randint(1,1000))  + "/"):
    """
        Get all events from bucket and upload them .

    """
    to_finish = datetime.datetime.strptime(to, "%Y-%m-%d")
    from_start  = datetime.datetime.strptime(from_, "%Y-%m-%d")
    s3 = boto3.client('s3')
    # from_bucket = s3.list_objects_v2(Bucket=bucket)
    # list_ = from_bucket['Contents']
    list_ = get_matching_s3_keys(bucket)
    list_ = order_by_event(list_)

    os.makedirs(os.path.dirname(download_path), exist_ok=True)
    for (e_date, s3_object) in list_:
        if from_start > e_date:
            continue;
        if to_finish < e_date:
            break
        name_obj = s3_object.split("/")[-1]
        # print(name_obj)
        e = download_path + name_obj
        s3.download_file(bucket, s3_object, e)
        print(e_date)
        event = Event(e)
        db = UseDynamoDB("Uploading", verbose=False)

        db.store_event(table_name, event)

    #delet content dir
    files = glob.glob(download_path+"*")
    for f in files:
        os.remove(f)


def upload_event_handler(path, table_name):
    """Upload without tracing.
    Util for lambda function
    Now path is one file"""
    # events = get_structure(path)
    event = Event(path)
    db = UseDynamoDB("Uploading", verbose=False)
    db.store_event(table_name, event)




def handler(event, context):
    for record in event['Records']:
        bucket = record['s3']['bucket']['name']
    key = record['s3']['object']['key']
    download_path = '/tmp/{}{}'.format(uuid.uuid4(), key)

    print("Downloading log in bucket {} with key {}".format(bucket, key))
    os.makedirs(os.path.dirname(download_path), exist_ok=True)
    print("bucket %s , key %s , download_path %s" % (bucket, key, download_path))


def main():
    args = parser.parse_args()
    path = args.path
    to = args.t
    from_ = args.f
    bucket_name = args.bucket_name
    table_name = 'alucloud' + os.environ['ID'] + '-ctt'
    # bucket_name = "cursocloudaws-trail"
    if bucket_name:
        print("bucket_name {}".format(bucket_name))
        upload_events_from_bucket(bucket_name, to,from_, table_name)
    else:
        print("path {}".format(path))
        upload_events(path, table_name, to, from_)
    # print(settings.table_name)


if (__name__ == '__main__'):
    main()