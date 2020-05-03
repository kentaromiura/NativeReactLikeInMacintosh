(function(global){
    global.Dialog = function(descriptor){
        var message = descriptor.children;
        var title = descriptor.properties.title;
        var onYes = descriptor.properties.onYes;
        var onNo = descriptor.properties.onNo;
        global.React.duktape.showDialog(title, message, onYes, onNo);
    };
    global.MessageBox = function(descriptor) {
        var message = descriptor.children;
        global.React.duktape.showMessageBox(message);
        return 0;
    };
    global.React = {
        native: {
            'Dialog': Dialog,
            'MessageBox': MessageBox
        },
        duktape: {},
        createElement: function (component, properties, children) {
            return {
                component: component,
                properties: properties,
                children: children
            }
        },
        mount: function(root) {
            var handled;
            Object.keys(global.React.native).forEach(function (component) {
                if(global.React.native[component] == root.component) {
                    handled = function workaroundForBug() {root.component(root)};
                }
            });
            if (handled) handled();
            if (!handled) {
                var newRoot = root.component(
                    Object.assign(
                        {
                            children: root.children
                        },
                        root.properties
                    )
                );
                newRoot.component(newRoot);
            }
        }
    };
})(new Function('return this')());