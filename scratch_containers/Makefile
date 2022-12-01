
TAG     ?= r32.7.1
L4T_JETPACK_REGISTRY ?= "nvcr.io/nvidia/l4t-jetpack"

image:
	docker build -t $(L4T_JETPACK_REGISTRY):$(TAG) \
		--build-arg "TAG=$(TAG)" \
		-f ./Dockerfile.jetpack .
