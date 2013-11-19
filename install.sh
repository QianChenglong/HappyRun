# =============================================================================
#      FileName: install.sh
#          Desc: 安装或卸载
#        Author: QianChengLong
#         Email: qian_cheng_long@163.com
#      HomePage: www.QianChengLong.com
#       Version: 1.0
#    LastChange: 2013-09-06 23:47:12
#       History:
# =============================================================================

usage() {
cat << EOF
usage: $0 options

OPTIONS:
  -i    Install Run
  -u    Update Run
  -r    Remove Run

Example Usage: $0 -i
EOF
}

install() {
    cp -v "./0-0-2/src/HappyRun" "/bin"
    # cp -v "HappyRun.desktop" "/etc/xdg/autostart/"
}

update() {
    remove
    install
}

remove() {
    rm -v "/bin/HappyRun"
    # rm -v "/etc/xdg/autostart/HappyRun.desktop"
}

if (( $# == 0 )); then
    make -C 0-0-2/src
    sudo ./install.sh -u
    exit 0
fi

# Make sure only root can run our script
if [[ $USER != 'root' ]]; then
    echo "Please run in root!"
    exit 1
fi

if (( $# != 1 )); then
    usage
    exit 1
fi

while getopts ":hiur" opt; do
    case $opt in
        h)
            HELP="True"
            ;;
        i)
            INSTALL="True"
            ;;
        u)
            UPDATE="True"
            ;;
        r)
            REMOVE="True"
            ;;
        *)
            usage
            exit 1
            ;;
    esac
done

if [[ $HELP ]]; then
    usage
    exit 0
fi

if [[ $INSTALL ]]; then
    echo "Install HappyRun ..."
    install
fi

if [[ $UPDATE ]]; then
    echo "Update HappyRun ..."
    update
fi
