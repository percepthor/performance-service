# Percepthor Performance Service

### Development

```
sudo docker run \
  -it \
  --name performance --rm \
  -p 5100:5100 --net percepthor \
  -v /home/ermiry/Documents/Work/percepthor/performance-service:/home/performance \
  -e RUNTIME=development \
  -e PORT=5100 \
  -e CERVER_RECEIVE_BUFFER_SIZE=4096 -e CERVER_TH_THREADS=4 \
  -e CERVER_CONNECTION_QUEUE=4 \
  itpercepthor/performance-service:development /bin/bash
```

### Test

```
sudo docker run \
  -it \
  --name performance --rm \
  -p 5100:5100 --net percepthor \
  -e RUNTIME=test \
  -e PORT=5100 \
  -e CERVER_RECEIVE_BUFFER_SIZE=4096 -e CERVER_TH_THREADS=4 \
  -e CERVER_CONNECTION_QUEUE=4 \
  itpercepthor/performance-service:test /bin/bash
```

### Production

```
sudo docker run \
  -d \
  --name performance --rm \
  -p 5100:5100 --net percepthor \
  -e RUNTIME=production \
  -e PORT=5100 \
  -e CERVER_RECEIVE_BUFFER_SIZE=4096 -e CERVER_TH_THREADS=4 \
  -e CERVER_CONNECTION_QUEUE=4 \
  itpercepthor/performance-service:production
```

### Main

#### GET /api/performance
**Access:** Public \
**Description:** Performance service top level route \
**Returns:**
  - 200 on success

#### GET api/performance/version
**Access:** Public \
**Description:** Returns performance service current version \
**Returns:**
  - 200 on success
