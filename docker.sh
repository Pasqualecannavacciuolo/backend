docker build -t ubuntu .
docker run -d --rm --name server -p 5193:5193 ubuntu /usr/src/server/server