let showMessageBox = message => {
    React.mount(<MessageBox>{message}</MessageBox>);
}

let nop = () => {};

let YesNoDialog = ({
    onYes = nop,
    onNo = nop,
    message = '',
    title = ''
}) => (
    <Dialog
        title={title}
        onYes={onYes}
        onNo={onNo}
    >
        {message}
    </Dialog>
);

let main = () => (
    <YesNoDialog
        title={'Attention!'}
        onYes={() => showMessageBox('Ok, bye then!')}
        onNo={() => showMessageBox('Alas there is not much more to do here!')}
        message={'Are you sure you want to quit?'}
    />
);