.type	_DrawEntireBackground,function
_DrawEntireBackground:
	pushl	%ebp
	movl	%esp,%ebp
	subl	$428,%esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi
	.line	125
	.line	147
	movl	_CameraY,%eax
	subl	_CameraYOffset,%eax
	movl	%eax,-304(%ebp)
	.line	148
	movl	_CameraX,%eax
	testl	%eax,%eax
	jge	_$227
	addl	$31,%eax
_$227:
	sarl	$5,%eax
	movl	%eax,-312(%ebp)
	.line	149
	movl	-304(%ebp),%eax
	testl	%eax,%eax
	jge	_$228
	addl	$31,%eax
_$228:
	sarl	$5,%eax
	movl	%eax,-316(%ebp)
	.line	151
	movl	_CameraX,%eax
	movl	$32,%ecx
	cdq
	idivl	%ecx
	movl	%edx,-80(%ebp)
	.line	152
	movl	-304(%ebp),%eax
	movl	$32,%ecx
	cdq
	idivl	%ecx
	movl	%edx,-308(%ebp)
	.line	154
	.line	155
	call	_DrawParallaxBackground
	.line	156
	movl	_LevelX,%eax
	subl	$21,%eax
	movl	%eax,-84(%ebp)
	.line	158
	movl	-308(%ebp),%eax
	negl	%eax
	movl	%eax,-48(%ebp)
	.line	159
	movl	-308(%ebp),%eax
	negl	%eax
	addl	$32,%eax
	movl	%eax,-40(%ebp)
	.line	160
	movl	-80(%ebp),%eax
	negl	%eax
	movl	%eax,-52(%ebp)
	.line	161
	movl	-80(%ebp),%eax
	negl	%eax
	addl	$32,%eax
	movl	%eax,-44(%ebp)
	.line	163
	movl	$27,%ecx
	xor	%edi,%edi
	leal	-300(%ebp),%eax
	xchg	%eax,%edi
	rep
	stosl
	.line	164
	movl	$108,-300(%ebp)
	.line	166
	movl	$27,%ecx
	xor	%edi,%edi
	leal	-192(%ebp),%eax
	xchg	%eax,%edi
	rep
	stosl
	.line	167
	movl	$108,-192(%ebp)
	.line	169
	pushl	$0
	pushl	$1
	leal	-300(%ebp),%eax
	pushl	%eax
	pushl	$0
	movl	_lpDDSBack2,%eax
	pushl	%eax
	movl	(,%eax),%edi
	call	*100(%edi)
	movl	%eax,%ebx
	.line	170
	or	%ebx,%ebx
	je	_$186
	pushl	$21
	pushl	%ebx
	call	_HandleBadResult
	addl	$8,%esp
_$186:
	.line	172
	pushl	$0
	pushl	$1
	leal	-192(%ebp),%eax
	pushl	%eax
	pushl	$0
	movl	_lpDDSBlocks,%eax
	pushl	%eax
	movl	(,%eax),%edi
	call	*100(%edi)
	movl	%eax,%ebx
	.line	173
	or	%ebx,%ebx
	je	_$188
	pushl	$22
	pushl	%ebx
	call	_HandleBadResult
	addl	$8,%esp
_$188:
	.line	174
	movl	-264(%ebp),%eax
	movl	%eax,-16(%ebp)
	.line	175
	movl	-284(%ebp),%eax
	movl	%eax,-28(%ebp)
	.line	177
	movl	-156(%ebp),%eax
	movl	%eax,-12(%ebp)
	.line	178
	movl	-176(%ebp),%eax
	movl	%eax,-24(%ebp)
	.line	179
	movl	-316(%ebp),%eax
	imull	_LevelX,%eax
	addl	-312(%ebp),%eax

	movl	%eax,-56(%ebp)
	.line	180
	movl	$0,-76(%ebp)
_$194:
	.line	182
	movl	$0,-36(%ebp)
_$198:
	.line	185
	movl	-56(%ebp),%eax
	movl	_level,%edx
	movzbl	(%edx,%eax),%eax
	movl	%eax,-32(%ebp)
	cmpl    $0,-32(%ebp)
	je _$202
	.line	186
	leal	-72(%ebp),%edi
	movl	-32(%ebp),%esi
	sall	$4,%esi
	leal	_PreComp(,%esi),%esi
	movl	$4,%ecx
	rep
	movsl
	.line	187
	cmpl $0,-76(%ebp)
	je _clipy
	.line	189

	movl	-68(%ebp),%eax
	imull	-24(%ebp),%eax
	addl	-72(%ebp),%eax
	movl	%eax,-4(%ebp)


	.line	190
	movl	-76(%ebp),%edi
	sall	$5,%edi
	subl    -308(%ebp),%edi
	imull	-28(%ebp),%edi
	movl	-36(%ebp),%esi
	sall	$5,%esi
	subl    -80(%ebp),%esi
	addl	%esi,%edi
	movl	%edi,-8(%ebp)
	movl    $32,-20(%ebp)
	jmp _noclipy
_clipy:


	movl	-68(%ebp),%eax
	addl    -308(%ebp),%eax
	imull	-24(%ebp),%eax
	addl	-72(%ebp),%eax
	movl	%eax,-4(%ebp)


	.line	190
	movl	-36(%ebp),%esi
	sall	$5,%esi
	subl    -80(%ebp),%esi
	movl	%esi,-8(%ebp)

	movl    $32,%eax
	movl    -308(%ebp),%edi
	subl    %edi,%eax


	movl    %eax,-20(%ebp)


	.line	190


_noclipy:


	.line	191
	;movl	$0,-20(%ebp)
_$205:
	.line	193
	;xorl	%ebx,%ebx
_$209:
	.line	196
	cmpl $0,-36(%ebp)
	je _clipxstart
	cmpl $20,-36(%ebp)
	je _clipxend
	;movl	-8(%ebp),%eax
	;incl	-8(%ebp)
	;movl	-4(%ebp),%edx
	;incl	-4(%ebp)
	;movl	-16(%ebp),%ecx
	;movl	%ecx,-428(%ebp)
	;movl	-12(%ebp),%ecx
	;movb	(%ecx,%edx),%dl
	;movl	-428(%ebp),%ecx
	;movb	%dl,(%ecx,%eax)


	movl -4(%ebp),%eax
	addl $32,-4(%ebp)
	movl -12(%ebp),%esi
	addl %eax,%esi

	movl -8(%ebp),%eax
	addl $32,-8(%ebp)
	movl -16(%ebp),%edi
	addl %eax,%edi

	movl $8,%ecx

	rep
    movsl








	.line	193
	;incl	%ebx
	;cmpl	$8,%ebx
	;jl	_$209

	.line	199
	movl	-24(%ebp),%eax
	subl	$32,%eax
	addl	%eax,-4(%ebp)
	.line	200
	movl	-28(%ebp),%eax
	subl	$32,%eax
	addl	%eax,-8(%ebp)
	.line	191
	jmp _noclipx

_clipxstart:
	movl -80(%ebp),%ecx
	addl %ecx,-4(%ebp)
	addl %ecx,-8(%ebp)

	xchgl  %ecx,%eax
	movl $32,%ecx
	subl %eax,%ecx

	movl -4(%ebp),%eax
	addl %ecx,-4(%ebp)
	movl -12(%ebp),%esi
	addl %eax,%esi



	movl -8(%ebp),%eax
	addl %ecx,-8(%ebp)
	movl -16(%ebp),%edi
	addl %eax,%edi



	rep
    movsb

	movl -80(%ebp),%eax
	movl $32,%ecx
	subl %eax,%ecx

	movl	-24(%ebp),%eax
	addl	%eax,-4(%ebp)
	subl	$32,-4(%ebp)
	.line	200
	movl	-28(%ebp),%eax
	addl	%eax,-8(%ebp)
	subl	$32,-8(%ebp)
	jmp _noclipx

_clipxend:

	movl -80(%ebp),%ecx

	movl -4(%ebp),%eax
	addl %ecx,-4(%ebp)
	movl -12(%ebp),%esi
	addl %eax,%esi



	movl -8(%ebp),%eax
	addl %ecx,-8(%ebp)
	movl -16(%ebp),%edi
	addl %eax,%edi



	rep
    movsb

	movl -80(%ebp),%ecx

	movl	-24(%ebp),%eax
	addl	%eax,-4(%ebp)
	subl	%ecx,-4(%ebp)
	.line	200
	movl	-28(%ebp),%eax
	addl	%eax,-8(%ebp)
	subl	%ecx,-8(%ebp)


_noclipx:
	decl	-20(%ebp)
	cmpl	$0,-20(%ebp)
	jg	_$205
	.line	205
_$202:

	.line	207
	incl	-56(%ebp)
	.line	208
	addl	$32,-44(%ebp)
	.line	209
	addl	$32,-52(%ebp)
	.line	182
	incl	-36(%ebp)
	cmpl	$21,-36(%ebp)
	jl	_$198
_skipline:
	.line	213
	movl	-84(%ebp),%eax
	addl	%eax,-56(%ebp)
	.line	214
	movl	-80(%ebp),%eax
	negl	%eax
	movl	%eax,-52(%ebp)
	.line	215
	movl	-80(%ebp),%eax
	negl	%eax
	addl	$32,%eax
	movl	%eax,-44(%ebp)
	.line	216
	addl	$32,-48(%ebp)
	.line	217
	addl	$32,-40(%ebp)
	.line	180
	incl	-76(%ebp)
	cmpl	$15,-76(%ebp)
	jl	_$194
	.line	219
	pushl	$0
	movl	_lpDDSBlocks,%eax
	pushl	%eax
	movl	(,%eax),%ebx
	call	*128(%ebx)
	.line	220
	pushl	$0
	movl	_lpDDSBack2,%eax
	pushl	%eax
	movl	(,%eax),%ebx
	call	*128(%ebx)
	.line	221
	popl	%edi
	popl	%esi
	popl	%ebx
	leave
	ret
_$229:
	.size	_DrawEntireBackground,_$229-_DrawEntireBackground
	.globl	_DrawEntireBackground

.extern	_strcpy
	.extern	_MoveRect
	.extern	_CanRectMove
	.extern	_HandleBadResult
	.extern	_memset
	.bss
	.globl	_PreComp
	.type	_PreComp,object
	.comm	_PreComp,4080
	.globl	_CameraYOffset
	.align	2
	.type	_CameraYOffset,object
	.comm	_CameraYOffset,4
	.globl	_CameraY
	.align	2
	.type	_CameraY,object
	.comm	_CameraY,4
	.globl	_CameraX
	.align	2
	.type	_CameraX,object
	.comm	_CameraX,4
	.extern	_Baseframes
	.extern	_DeleteBullet
	.extern	_ClearSurface
	.extern	_NumSwitches
	.extern	_Switches
	.extern	_NumChains
	.extern	_NumPlatforms
	.extern	_Platforms
	.extern	_Chains
	.extern	_GetSprite
	.extern	_bullets
	.extern	_Player
	.extern	_NumSprites
	.extern	_spritedefs
	.extern	_LevelY
	.extern	_LevelX
	.extern	_physics
	.extern	_level
	.extern	_lpDDSBackground
	.extern	_lpDDSSystem
	.extern	_lpDDSSprites
	.extern	_lpDDSBack2
	.extern	_lpDDSBlocks
	.globl	_IID_IDirectDrawClipper
	.type	_IID_IDirectDrawClipper,object
	.comm	_IID_IDirectDrawClipper,16
	.globl	_IID_IDirectDrawPalette
	.type	_IID_IDirectDrawPalette,object
	.comm	_IID_IDirectDrawPalette,16
	.globl	_IID_IDirectDrawSurface2
	.type	_IID_IDirectDrawSurface2,object
	.comm	_IID_IDirectDrawSurface2,16
	.globl	_IID_IDirectDrawSurface
	.type	_IID_IDirectDrawSurface,object
	.comm	_IID_IDirectDrawSurface,16
	.globl	_IID_IDirectDraw2
	.type	_IID_IDirectDraw2,object
	.comm	_IID_IDirectDraw2,16
	.globl	_IID_IDirectDraw
	.type	_IID_IDirectDraw,object
	.comm	_IID_IDirectDraw,16
	.globl	_CLSID_DirectDrawClipper
	.type	_CLSID_DirectDrawClipper,object
	.comm	_CLSID_DirectDrawClipper,16
	.globl	_CLSID_DirectDraw
	.type	_CLSID_DirectDraw,object
	.comm	_CLSID_DirectDraw,16
	.globl	_GUID_CUSTOM_CONFIRMOBJECTSAFETY
	.type	_GUID_CUSTOM_CONFIRMOBJECTSAFETY,object
	.comm	_GUID_CUSTOM_CONFIRMOBJECTSAFETY,16
	.globl	_CLSID_SoftDistExt
	.type	_CLSID_SoftDistExt,object
	.comm	_CLSID_SoftDistExt,16
	.globl	_SID_BindHost
	.type	_SID_BindHost,object
	.comm	_SID_BindHost,16
	.extern	_GetTickCount@0
	.extern	_wsprintfA
.globl	_DrawParallaxBackground
