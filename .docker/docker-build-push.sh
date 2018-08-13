#!/usr/bin/env bash
##
# Build and push images to Dockerhub.
#

if [ -f .env ] ; then source .env; elif [ -f ../.env ] ; then source ../.env; else echo "Environment variables file not found"; exit 1; fi

# Namespace for the image.
DOCKERHUB_NAMESPACE=${DOCKERHUB_NAMESPACE:-govcms}
# Name of the project. Image with code in it will get this name.
DOCKERHUB_PROJECT=${DOCKERHUB_PROJECT:-govcms7}
# Docker image version tag.
IMAGE_VERSION_TAG=${IMAGE_VERSION_TAG:-}
# Docker image tag prefix to be stripped from tag. Use " " (space) value to
# prevent stripping of the version.
IMAGE_VERSION_TAG_PREFIX=${IMAGE_VERSION_TAG_PREFIX:-7.x-}
# Docker image edge tag.
IMAGE_TAG_EDGE=${IMAGE_TAG_EDGE:-beta}

# Path prefix to Dockerfiles.
FILE_PREFIX=${FILE_PREFIX:-Dockerfile.}

for file in $(echo $FILE_PREFIX"*"); do
    service=${file/$FILE_PREFIX/}

    version_tag=$IMAGE_VERSION_TAG
    [ "$IMAGE_VERSION_TAG_PREFIX" != "" ] && version_tag=${IMAGE_VERSION_TAG/$IMAGE_VERSION_TAG_PREFIX/}

    project=${service}
    [ "$service" == "cli" ] && project=$DOCKERHUB_PROJECT

    echo "==> Building \"$service\" image from file $file for project \"$DOCKERHUB_NAMESPACE/$project\""
    docker build -f $file -t $service .
    docker tag $service $DOCKERHUB_NAMESPACE/$project:$IMAGE_TAG_EDGE

    [ "$version_tag" != "" ] && echo "==> Tagging and pushing \"$service\" image to $DOCKERHUB_NAMESPACE/$project:$version_tag" && docker tag $service $DOCKERHUB_NAMESPACE/$project:$version_tag && docker push $DOCKERHUB_NAMESPACE/$project:$version_tag
    echo "==> Tagged and pushed \"$service\" image to $DOCKERHUB_NAMESPACE/$project:$IMAGE_TAG_EDGE" && docker push $DOCKERHUB_NAMESPACE/$project:$IMAGE_TAG_EDGE
done
