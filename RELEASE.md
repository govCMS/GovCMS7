# govCMS Releases

## Releasing Docker images
1. Tag codebase in git with a version.
2. This will trigger CI build that will build images, tag them with version and edge tags, and will push them to Dockerhub.
```
ahoy push
```
3. Once the images are ready to be released to public, images manually tagged as latest and pushed to Dockerhub.
```
ahoy release
```
