#!/bin/bash
channeld_version=v0.5.0

# Get this script's path
script_dir=$(cd "$(dirname "$0")"; pwd)

# if default channeld path is different from CHANNELD_PATH, do nothing
defualt_channeld_path=$script_dir/channeld

tmp_path=${CHANNELD_PATH/:/}
tmp_path=${tmp_path//\\/\/}
disk_id=${tmp_path:0:1}
disk_id=$(echo $disk_id | tr [:upper:] [:lower:])
other_path=${tmp_path:1}
local_channeld=/${disk_id}${other_path}

if [ "$defualt_channeld_path" != $local_channeld ]; then
    echo "The channeld is not include in ChanneldUE, please update channeld by yourself"
    echo "    The channeld path is: $local_channeld"
    echo "    The default channeld path is: $defualt_channeld_path"
    exit 0
fi

echo Updating channeld...

# Update channeld to latest version
cd "$CHANNELD_PATH"

# If channeld_version is not equal to current git tag, update channeld to channeld_version
if [ $(git describe --tags) != $channeld_version ]; then
    echo "Update channeld to ${channeld_version}..."
    git pull origin $channeld_version
    if [ $? -ne 0 ]; then
        echo "ERROR: Please handle the conflict of channeld[$channeld_version], and then run this script again[$script_dir]"
        exit 1
    fi
    git checkout $channeld_version
    if [ $? -ne 0 ]; then
        echo "ERROR: Please handle the conflict of channeld[$channeld_version], and then run this script again[$script_dir]"
        exit 1
    fi

    # Install go modules of channeld
    export GOPROXY=https://goproxy.io,direct
    go mod download -x
    go install google.golang.org/protobuf/cmd/protoc-gen-go@v1.28
    go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@v1.2

    echo "Update channeld to ${channeld_version} completed"
else
    echo "The local channeld is the latest version: ${channeld_version}"
fi

