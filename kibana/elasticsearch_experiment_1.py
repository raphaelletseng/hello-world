from datetime import datetime
from elasticsearch import Elasticsearch
es = Elasticsearch()

doc = {"author": "raph",
       "text": "raph says hello world!",
       'timestamp': datetime.now()}
res = es.index(index='test-index',  doc_type='tweet', id=1, body=doc)
print(res['result'])

res = es.get(index='test-index',doc_type='tweet', id=1)
print(res['_source'])
es.indices.refresh(index='test-index')
res = es.search(index="test-index", body={"query":{"match_all": {}}})
print("Got %d hits:" %res['hits']['total']['value'])
for hit in res['hits']['hits']:
       print("%(timestamp)s %(author)s : %(text)s" %hit["_source"])
