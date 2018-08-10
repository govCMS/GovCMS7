#!/usr/bin/env bash
##
# Build and push images to Dockerhub.
#

if [ -f .env ] ; then source .env; elif [ -f ../.env ] ; then source ../.env; else echo "Environment variables file not found"; exit 1; fi

# Namespace for the image.
DOCKERHUB_NAMESPACE=${DOCKERHUB_NAMESPACE:-govcms}
# Name of the project. Image with code in it will get this name.
DOCKERHUB_PROJECT=${DOCKERHUB_PROJECT:-govcms7}
# Docker image edge tag.
IMAGE_TAG_EDGE=${IMAGE_TAG_EDGE:-beta}

# Path prefix to Dockerfiles.
FILE_PREFIX=${FILE_PREFIX:-Dockerfile.}

for file in $(echo $FILE_PREFIX"*"); do
    service=${file/$FILE_PREFIX/}

    project=${service}
    [ "$service" == "cli" ] && project=$DOCKERHUB_PROJECT

    echo "==> Releasing \"$service\" image for project \"$DOCKERHUB_NAMESPACE/$project\""
    docker pull $DOCKERHUB_NAMESPACE/$project:$IMAGE_TAG_EDGE
    docker tag $service $DOCKERHUB_NAMESPACE/$project:latest
    echo "==> Tagging and pushing \"$service\" image to $DOCKERHUB_NAMESPACE/$project:latest" && docker push $DOCKERHUB_NAMESPACE/$project:latest
done
